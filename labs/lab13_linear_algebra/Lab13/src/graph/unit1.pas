unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls, Math;

type
  { TForm1 }
  TForm1 = class(TForm)
    graphic: TImage;
    graphPanel: TPanel;
    lblStatus: TLabel;
    procedure FormCreate(Sender: TObject);
  private
  public
  end;

var
  Form1: TForm1;
  // Данные из temp_data.txt
  gA1, gB1, gC1: real;
  gA2, gB2, gC2: real;
  gStatus: integer;
  gPX, gPY: real;
  gX_min, gX_max, gY_min, gY_max: real;

implementation

{$R *.lfm}

// -------------------------------------------------------
// Та же функция что и у тебя
// -------------------------------------------------------
function toScrPos(scr_beg, scr_end, val, val_beg, val_end: real): real;
begin
  if (val_end - val_beg) = 0 then
    toScrPos := scr_beg
  else
    toScrPos := ((val - val_beg) * (scr_end - scr_beg)) / (val_end - val_beg) + scr_beg;
end;

// -------------------------------------------------------
// Оси — почти твоя drawAxis, только метки по всей шкале
// -------------------------------------------------------
procedure drawAxis(x_min, x_max, y_min, y_max: real);
var
  cenX, cenY, i, sx, sy: integer;
begin
  with Form1.graphic.Canvas do begin
    cenX := round(toScrPos(0, Form1.graphic.Width,  0, x_min, x_max));
    cenY := round(toScrPos(Form1.graphic.Height, 0, 0, y_min, y_max));

    Brush.Color := clForm;
    FillRect(0, 0, Form1.graphic.Width, Form1.graphic.Height);

    Pen.Color := clBlack;
    Pen.Width := 1;

    // Оси
    Line(0, cenY, Form1.graphic.Width, cenY);
    Line(cenX, 0, cenX, Form1.graphic.Height);

    // Стрелки
    Line(Form1.graphic.Width-5, cenY-5, Form1.graphic.Width, cenY);
    Line(Form1.graphic.Width-5, cenY+5, Form1.graphic.Width, cenY);
    Line(cenX-5, 5, cenX, 0);
    Line(cenX+5, 5, cenX, 0);

    // Подписи осей
    TextOut(Form1.graphic.Width - 15, cenY - 20, 'X');
    TextOut(cenX + 5, 5, 'Y');

    // Засечки X
    i := round(x_min);
    while i <= round(x_max) do begin
      if i <> 0 then begin
        sx := round(toScrPos(0, Form1.graphic.Width, i, x_min, x_max));
        Line(sx, cenY - 4, sx, cenY + 4);
        TextOut(sx - 4, cenY + 6, IntToStr(i));
      end;
      i := i + 1;
    end;

    // Засечки Y
    i := round(y_min);
    while i <= round(y_max) do begin
      if i <> 0 then begin
        sy := round(toScrPos(Form1.graphic.Height, 0, i, y_min, y_max));
        Line(cenX - 4, sy, cenX + 4, sy);
        TextOut(cenX + 6, sy - 7, IntToStr(i));
      end;
      i := i + 1;
    end;
  end;
end;

// -------------------------------------------------------
// Рисует прямую Ax + By = C через всю область
// -------------------------------------------------------
procedure drawLine(A, B, C: real; color: TColor);
var
  x1, y1, x2, y2: real;
  sx1, sy1, sx2, sy2: integer;
begin
  // Берём две точки на границах области по X
  // Если B = 0 — вертикальная прямая
  if abs(B) > 1e-12 then begin
    x1 := gX_min; y1 := (C - A * x1) / B;
    x2 := gX_max; y2 := (C - A * x2) / B;
  end else if abs(A) > 1e-12 then begin
    // вертикальная: x = C/A
    x1 := C / A; y1 := gY_min;
    x2 := C / A; y2 := gY_max;
  end else
    Exit; // вырожденный случай

  sx1 := round(toScrPos(0, Form1.graphic.Width,  x1, gX_min, gX_max));
  sy1 := round(toScrPos(Form1.graphic.Height, 0, y1, gY_min, gY_max));
  sx2 := round(toScrPos(0, Form1.graphic.Width,  x2, gX_min, gX_max));
  sy2 := round(toScrPos(Form1.graphic.Height, 0, y2, gY_min, gY_max));

  with Form1.graphic.Canvas do begin
    Pen.Color := color;
    Pen.Width := 2;
    MoveTo(sx1, sy1);
    LineTo(sx2, sy2);
  end;
end;

// -------------------------------------------------------
// Точка пересечения
// -------------------------------------------------------
procedure drawPoint(px, py: real);
var
  spx, spy: integer;
begin
  spx := round(toScrPos(0, Form1.graphic.Width,  px, gX_min, gX_max));
  spy := round(toScrPos(Form1.graphic.Height, 0, py, gY_min, gY_max));

  with Form1.graphic.Canvas do begin
    Pen.Color   := clGreen;
    Brush.Color := clGreen;
    Ellipse(spx - 5, spy - 5, spx + 5, spy + 5);
    Font.Color := clGreen;
    Font.Size  := 9;
    TextOut(spx + 8, spy - 10,
      '(' + FormatFloat('0.##', px) + '; ' + FormatFloat('0.##', py) + ')');
  end;
end;

// -------------------------------------------------------
// Читаем temp_data.txt и рисуем всё
// -------------------------------------------------------
procedure drawGraphic;
var
  f: TextFile;
begin
  AssignFile(f, 'temp_data.txt');
  try
    Reset(f);
    Readln(f, gA1, gB1, gC1);
    Readln(f, gA2, gB2, gC2);
    Readln(f, gStatus);
    Readln(f, gPX, gPY);
    CloseFile(f);
  except
    Form1.lblStatus.Caption := 'Error reading temp_data.txt';
    Exit;
  end;

  // Область просмотра вокруг точки пересечения
  if gStatus = 1 then begin
    gX_min := gPX - 10; gX_max := gPX + 10;
    gY_min := gPY - 10; gY_max := gPY + 10;
  end else begin
    gX_min := -10; gX_max := 10;
    gY_min := -10; gY_max := 10;
  end;

  drawAxis(gX_min, gX_max, gY_min, gY_max);
  drawLine(gA1, gB1, gC1, clBlue);
  drawLine(gA2, gB2, gC2, clRed);

  case gStatus of
    1:  begin
          drawPoint(gPX, gPY);
          Form1.lblStatus.Caption :=
            'Intersection: (' + FormatFloat('0.####', gPX) +
            ', '              + FormatFloat('0.####', gPY) + ')';
        end;
    0:  Form1.lblStatus.Caption := 'Lines are identical';
   -1:  Form1.lblStatus.Caption := 'Lines are parallel';
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  drawGraphic;
end;

end.

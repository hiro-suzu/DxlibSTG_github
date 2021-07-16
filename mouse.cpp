//マウス処理のソースファイル

//ヘッダーファイル読み込み      
#include"game.h"
#include"mouse.h" 
#include"FPS.h"

//マウス入力を取得
MOUSE mouse;

/// <summary>
/// マウスの入力情報を取得
/// </summary>
/// <returns></returns>
VOID MouseUpdate(VOID)
{
   //マウスの以前の情報を取得
    mouse.OldPoint = mouse.Point;

    //マウスの以前のボタン入力を取得
    mouse.OldButton[MOUSE_INPUT_LEFT] = mouse.Button[MOUSE_INPUT_LEFT];
    mouse.OldButton[MOUSE_INPUT_MIDDLE] = mouse.Button[MOUSE_INPUT_MIDDLE];
    mouse.OldButton[MOUSE_INPUT_RIGHT] = mouse.Button[MOUSE_INPUT_RIGHT];

    //マウスの座標を取得の座標を取得
    GetMousePoint(&mouse.Point.x, &mouse.Point.y);

    //マウスの座標が画面外の場合は、画面内に収める
    if (mouse.Point.x < 0) { mouse.Point.x = 0;}
    if (mouse.Point.x > GAME_WIDTH) { mouse.Point.x = GAME_WIDTH;}
    if (mouse.Point.y < 0) { mouse.Point.y = 0; }
    if (mouse.Point.y > GAME_HEIGHT) { mouse.Point.y = GAME_HEIGHT; }

    //マウスの推しているボタンを取得
    mouse.InputValue = GetMouseInput();

    //左ボタンを押しているかチェック（TRUEは0以外なので、2も4もTRUE)
    if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) {mouse.Button[MOUSE_INPUT_LEFT]++; } //押している
    if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) {mouse.Button[MOUSE_INPUT_LEFT] = 0; } //押していない

    //中ボタンを押しているかチェック（TRUEは0以外なので、2も4もTRUE)
    if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; } //押している
    if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; } //押していない

    //右ボタンを押しているかチェック（TRUEは0以外なので、2も4もTRUE)
    if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; } //押している
    if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; } //押していない

    //ホイールの回転量を取得
    mouse.WheelValue = GetMouseWheelRotVol();

    return;
}


BOOL MouseDown(int MOUSE_INPUT_)
{
    //マウスコードのボタンを押しているとき
    if (mouse.Button[MOUSE_INPUT_] != 0)
    {
        return TRUE;   //ボタンを押している
    }
    else
    {
        return FALSE;  //ボタンを押していない
    }
}


extern BOOL MouseUp(int MOUSE_INPUT_)
{

}
//マウス処理のヘッダファイル

//ヘッダーファイルの読み込み

//ゲームのメインヘッダファイル
#include "game.h"
#include "shape.h"

//マウスのボタン
#define MOUSE_BUTTON_CODE  129   //0x0000～0x0080まで

//マウスの構造体
struct MOUSE
{
	int InputValue = 0;  //GetMouseInputの値が入る
	int WheelValue = 0;  //マウスホイールの回転量（奥はプラス値 / 手前はマイナス値)
	iPOINT Point;					   //マウスの座標が入る
	iPOINT OldPoint;				   //マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE];  //マウスのボタン入力（直前）が入る
	int Button[MOUSE_BUTTON_CODE];  //マウスのボタン入力が入る
};

//マウス入力を取得
extern MOUSE mouse;


//プロトタイプ宣言
extern VOID MouseUpdate(VOID);		                                //マウスの入力情報を変更する
extern BOOL MouseDown(int MOUSE_INPUT_);		                    //ボタンを押しているか、マウスコードで判断する
extern BOOL MouseUp(int MOUSE_INPUT_);		                        //ボタンを押して上げたか、マウスコードで判断する
extern BOOL MouseDownKeep(int MOUSE_INPUT_, int milliTime);		    //ボタンを押して続けたか、マウスコードで判断する
extern BOOL MouseClick(int MOUSE_INPUT_);		                    //マウスをクリックしたか、マウスコードで判断する
extern VOID MouseDraw(VOID);		                                //マウスの情報を描画する

extern BOOL MouseRectClick(RECT rect, int MOUSE_INPUT_);		    //マウスが短形領域をクリックしたか
extern BOOL MouseMaruClick(MARU rect,int MOUSE_INPUT_);		        //マウスが円領域をクリックしたか

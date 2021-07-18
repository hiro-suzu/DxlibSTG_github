//図形のソースファイル

//ヘッダーファイル読み込み
#include"game.h"
#include"shape.h"
#include"math.h"

/// <summary>
/// 短形領域同士の当たり判定をする関数
/// </summary>
/// <param name="a">領域A</param>
/// <param name="b">領域B</param>
/// <returns></returns>
BOOL CheckCollRectToRect(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;  //当たっている
	}
	return FALSE;  //当たっていない
}

/// <summary>
/// 四角と点の当たり判定
/// </summary>
/// <param name="pt">iPOINT型の点</param>
/// <param name="r">短形領域</param>
/// <returns></returns>
BOOL CheckColliPointToRect(iPOINT pt, RECT r)
{
	if (
		pt.x > r.left && pt.x < r.right  //点のX位置が四角の左右の間にいて
		&& pt.y > r.top && pt.y < r.bottom //点のY位置が四角の上下の間にいる時
		)
	{
		return TRUE;
	}
	return FALSE;
}

/// <summary>
/// 円と点の当たり判定
/// </summary>
/// <param name="pt">iPOINT型の点</param>
/// <param name="m">円領域</param>
/// <returns></returns>
BOOL CheckColliPointToMaru(iPOINT pt, MARU m)
{
	//三角関数を求めよ
	float a = pt.x - m.center.x;  //三角形の底辺の長さを求める
	float b = pt.y - m.center.y;  //三角形の高さの長さを求める
	float c = sqrtf(a * a + b * b);  //三角形の斜辺の長さを求める

	//斜辺の長さが、円の半径よりも短いならば、円の中にいる
	if (c <= m.radius)
	{
		return TRUE;
	}
	return FALSE;
}

/// <summary>
/// 円と円の当たり判定
/// </summary>
/// <param name="maru1">円領域1</param>
/// <param name="maru2">円領域2</param>
/// <returns></returns>
BOOL CheckCollMaruToMaru(MARU maru1, MARU maru2)
{
	//三角関数を求めよ
	float a = maru1.center.x - maru2.center.x;  //三角形の底辺の長さを求める
	float b = maru1.center.y - maru2.center.y;  //三角形の高さの長さを求める
	float c = sqrtf(a * a + b * b);  //三角形の斜辺の長さを求める

	//斜辺の長さが、円の半径�@+円の半径�Aよりも短いならば、円の中にいる
	if (c <= maru1.radius + maru2.radius)
	{
		return TRUE;
	}
	return FALSE;
}
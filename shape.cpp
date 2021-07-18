//�}�`�̃\�[�X�t�@�C��

//�w�b�_�[�t�@�C���ǂݍ���
#include"game.h"
#include"shape.h"
#include"math.h"

/// <summary>
/// �Z�`�̈擯�m�̓����蔻�������֐�
/// </summary>
/// <param name="a">�̈�A</param>
/// <param name="b">�̈�B</param>
/// <returns></returns>
BOOL CheckCollRectToRect(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;  //�������Ă���
	}
	return FALSE;  //�������Ă��Ȃ�
}

/// <summary>
/// �l�p�Ɠ_�̓����蔻��
/// </summary>
/// <param name="pt">iPOINT�^�̓_</param>
/// <param name="r">�Z�`�̈�</param>
/// <returns></returns>
BOOL CheckColliPointToRect(iPOINT pt, RECT r)
{
	if (
		pt.x > r.left && pt.x < r.right  //�_��X�ʒu���l�p�̍��E�̊Ԃɂ���
		&& pt.y > r.top && pt.y < r.bottom //�_��Y�ʒu���l�p�̏㉺�̊Ԃɂ��鎞
		)
	{
		return TRUE;
	}
	return FALSE;
}

/// <summary>
/// �~�Ɠ_�̓����蔻��
/// </summary>
/// <param name="pt">iPOINT�^�̓_</param>
/// <param name="m">�~�̈�</param>
/// <returns></returns>
BOOL CheckColliPointToMaru(iPOINT pt, MARU m)
{
	//�O�p�֐������߂�
	float a = pt.x - m.center.x;  //�O�p�`�̒�ӂ̒��������߂�
	float b = pt.y - m.center.y;  //�O�p�`�̍����̒��������߂�
	float c = sqrtf(a * a + b * b);  //�O�p�`�̎Εӂ̒��������߂�

	//�Εӂ̒������A�~�̔��a�����Z���Ȃ�΁A�~�̒��ɂ���
	if (c <= m.radius)
	{
		return TRUE;
	}
	return FALSE;
}

/// <summary>
/// �~�Ɖ~�̓����蔻��
/// </summary>
/// <param name="maru1">�~�̈�1</param>
/// <param name="maru2">�~�̈�2</param>
/// <returns></returns>
BOOL CheckCollMaruToMaru(MARU maru1, MARU maru2)
{
	//�O�p�֐������߂�
	float a = maru1.center.x - maru2.center.x;  //�O�p�`�̒�ӂ̒��������߂�
	float b = maru1.center.y - maru2.center.y;  //�O�p�`�̍����̒��������߂�
	float c = sqrtf(a * a + b * b);  //�O�p�`�̎Εӂ̒��������߂�

	//�Εӂ̒������A�~�̔��a�@+�~�̔��a�A�����Z���Ȃ�΁A�~�̒��ɂ���
	if (c <= maru1.radius + maru2.radius)
	{
		return TRUE;
	}
	return FALSE;
}
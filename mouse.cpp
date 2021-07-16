//�}�E�X�����̃\�[�X�t�@�C��

//�w�b�_�[�t�@�C���ǂݍ���      
#include"game.h"
#include"mouse.h" 
#include"FPS.h"

//�}�E�X���͂��擾
MOUSE mouse;

/// <summary>
/// �}�E�X�̓��͏����擾
/// </summary>
/// <returns></returns>
VOID MouseUpdate(VOID)
{
   //�}�E�X�̈ȑO�̏����擾
    mouse.OldPoint = mouse.Point;

    //�}�E�X�̈ȑO�̃{�^�����͂��擾
    mouse.OldButton[MOUSE_INPUT_LEFT] = mouse.Button[MOUSE_INPUT_LEFT];
    mouse.OldButton[MOUSE_INPUT_MIDDLE] = mouse.Button[MOUSE_INPUT_MIDDLE];
    mouse.OldButton[MOUSE_INPUT_RIGHT] = mouse.Button[MOUSE_INPUT_RIGHT];

    //�}�E�X�̍��W���擾�̍��W���擾
    GetMousePoint(&mouse.Point.x, &mouse.Point.y);

    //�}�E�X�̍��W����ʊO�̏ꍇ�́A��ʓ��Ɏ��߂�
    if (mouse.Point.x < 0) { mouse.Point.x = 0;}
    if (mouse.Point.x > GAME_WIDTH) { mouse.Point.x = GAME_WIDTH;}
    if (mouse.Point.y < 0) { mouse.Point.y = 0; }
    if (mouse.Point.y > GAME_HEIGHT) { mouse.Point.y = GAME_HEIGHT; }

    //�}�E�X�̐����Ă���{�^�����擾
    mouse.InputValue = GetMouseInput();

    //���{�^���������Ă��邩�`�F�b�N�iTRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
    if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) {mouse.Button[MOUSE_INPUT_LEFT]++; } //�����Ă���
    if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) {mouse.Button[MOUSE_INPUT_LEFT] = 0; } //�����Ă��Ȃ�

    //���{�^���������Ă��邩�`�F�b�N�iTRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
    if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; } //�����Ă���
    if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; } //�����Ă��Ȃ�

    //�E�{�^���������Ă��邩�`�F�b�N�iTRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
    if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; } //�����Ă���
    if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; } //�����Ă��Ȃ�

    //�z�C�[���̉�]�ʂ��擾
    mouse.WheelValue = GetMouseWheelRotVol();

    return;
}


BOOL MouseDown(int MOUSE_INPUT_)
{
    //�}�E�X�R�[�h�̃{�^���������Ă���Ƃ�
    if (mouse.Button[MOUSE_INPUT_] != 0)
    {
        return TRUE;   //�{�^���������Ă���
    }
    else
    {
        return FALSE;  //�{�^���������Ă��Ȃ�
    }
}


extern BOOL MouseUp(int MOUSE_INPUT_)
{

}
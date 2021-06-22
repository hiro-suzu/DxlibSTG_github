//�w�b�_�[�t�@�C���ǂݍ���
#include"game.h"		//�Q�[���S�̂̃w�b�_�t�@�C��
#include "keyboard.h"	//�L�[�{�[�h�̏���
#include "FPS.h"		//FPS�̏���


//�\���̂̒�`
struct IMAGE
{
	int handle = -1;	//�摜�̃n���h��(�Ǘ��ԍ��j
	char path[255];		//�摜�̏ꏊ(�p�X)
	int x;				//X�ʒu
	int y;				//Y�ʒu
	int width;          //��
	int height;         //����

	BOOL IsDraw = FALSE;//�摜���`��ł���H

};

//�L�����N�^�̍\����
struct CHARACTOR
{
	IMAGE img;			//�摜�\����
	int speed = 1;		//�ړ����x
	RECT coll;			//�����蔻��̗̈�i�l�p�j
	

};

//����̍\����
struct MOVIE
{
	int handle = -1;		//����n���h��
	char path[255];			//����̃p�X

	int x;					//���ʒu
	int y;					//���ʒu
	int width;				//��
	int height;				//����

	int Volume = 255;		//�{�����[��(�ŏ��j�O�`255(�ő�j
};

struct AUDIO
{
	int handle = -1;	//���y�̃n���h��
	char path[255];		//���y�̃p�X

	int Volume = -1;	//�{�����[���iMIN 0�`255 MAX)
	int playType = -1;
};

//�O���[�o���ϐ�
//�V�[�����Ǘ�����ϐ�
GAME_SCENE GameScene;		//���݂̃Q�[���̃V�[��
GAME_SCENE OldGameScene;	//�O��̃Q�[���̃V�[��
GAME_SCENE NextGameScene;	//���̃Q�[���̃V�[��



//��ʂ̐؂�ւ�
BOOL IsFadeOut = FALSE;	//�t�F�[�h�A�E�g
BOOL IsFadeIn = FALSE;	//�t�F�[�h�C��

int fadeTimeMill = 2000;  //�؂�ւ��~���b
int fadeTimeMax = fadeTimeMill / 1000 * 60; //�~���b���t���[���b�ɕϊ�

//�t�F�[�h�A�E�g
int fadeOutCntInit = 0;				//�����l
int fadeOutCnt = fadeOutCntInit;	//�t�F�[�h�A�E�g�̃J�E���^
int fadeOutCntMax = fadeTimeMax;	//�t�F�[�h�A�E�g�̃J�E���^MAX

//�t�F�[�h�C��
int fadeInCntInit = fadeTimeMax;		//�����l
int fadeInCnt = fadeInCntInit;			//�t�F�[�h�C���̃J�E���^
int fadeInCntMax = fadeTimeMax;			//�t�F�[�h�C���̃J�E���^MAX



//�v���g�^�C�v�錾
VOID Title(VOID);		//�^�C�g�����
VOID TitleProc(VOID);	//�^�C�g�����(�����j
VOID TitleDraw(VOID);	//�^�C�g�����(�`��j

VOID Play(VOID);	//�v���C���
VOID PlayProc(VOID);//�v���C���(�����j
VOID PlayDraw(VOID);//�v���C���(�`��)

VOID End(VOID);		//�G���h���
VOID EndProc(VOID); //�G���h���(����)
VOID EndDraw(VOID); //�G���h��ʁi�`��j

VOID Change(VOID);		//�؂�ւ����
VOID ChangeProc(VOID);	//�؂�ւ����(����)
VOID ChangeDraw(VOID);	//�؂�ւ���ʁi�`��j

VOID ChangeScene(GAME_SCENE scene); //�V�[���؂�ւ�

VOID CollUpdatePlayer(CHARACTOR* chara); //�����蔻��̗̈���X�V
VOID CollUpdate(CHARACTOR* chara);       //�����蔻��

BOOL OnCollRECT(RECT a, RECT b);		//��`�Ƌ�`�̓����蔻��

BOOL GameLoad(VOID); //�Q�[���̃f�[�^�̓ǂݍ���

VOID GameInit(VOID); //�Q�[���̃f�[�^�̏�����

BOOL LoadImageMem(IMAGE* image, const char* path);	//�Q�[���摜�̓ǂݍ���
BOOL LoadAudio(AUDIO* audio, const char* path, int volume, int playType);	//�Q�[�����y�̓ǂݍ���

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{

	SetOutApplicationLogValidFlag(FALSE);              //Log,txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);                            //�E�B���h�E���[�h�̐ݒ�
	SetMainWindowText(GAME_TITLE);                     //�E�B���h�E�̃^�C�g������
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR); //�E�B���h�E�̉𑜓x��ݒ�
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);            //�E�B���h�E�̑傫����ݒ�
	SetBackgroundColor(255, 255, 255);                 //�f�t�H���g�̔w�i�̐F
	SetWindowIconID(GAME_ICON_ID);                     //�A�C�R���t�@�C����Ǎ�
	SetWindowStyleMode(GAME_WINDOW_BAR);               //�E�B���h�E�o�[�̏��
	SetWaitVSyncFlag(TRUE);                            //�f�B�X�v���C�̐���������L���ɂ���
	SetAlwaysRunFlag(TRUE);                            //�E�B���h�E�������ƃA�N�e�B�u�ɂ���

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)		
	{

		return -1;	// �G���[���N�����璼���ɏI��
	}

	//�_�u���o�b�t�@�����O�L����
	SetDrawScreen(DX_SCREEN_BACK);

	//�ŏ��̃V�[���́A�^�C�g����ʂ���
	GameScene = GAME_SCENE_TITLE;

	//�Q�[���S�̂̏�����
	if (!GameLoad())
	{
		//�f�[�^�̓ǂݍ��݂Ɏ��s�����Ƃ�
		DxLib_End();
		return -1;
	}
	
	//�Q�[���̏�����
	GameInit();

	//�������[�v
	while (1)
	{
		if (ProcessMessage() != 0) {break;}//���b�Z�[�W���󂯎�葱����
		if (ClearDrawScreen() != 0) {break;}

		//�L�[�{�[�h���͂̍X�V
		AllKeyUpdate();

		//FPS�l�̍X�V
		FPSUpdate();

		//ESC�L�[�ŋ����I��
		if (KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break;}

		//�ȑO�̃V�[�����擾
		if (GameScene != GAME_SCENE_CHANGE)
		{
			OldGameScene = GameScene;
		}


		switch (GameScene)
		{
		case GAME_SCENE_TITLE:
			Title();		//�^�C�g�����
			break;
		case GAME_SCENE_PLAY:
			Play();		//�v���C���
			break;
		case GAME_SCENE_END:
			End();		//�G���h���
			break;
		case GAME_SCENE_CHANGE:
			Change();		//�؂�ւ����
			break;
		default:
			break;
		}

		//�V�[����؂�ւ���
		if (OldGameScene != GameScene)
		{
			//���݂̃V�[�����؂�ւ���ʂłȂ��Ƃ�
			if (GameScene != GAME_SCENE_CHANGE)
			{
				NextGameScene = GameScene; //���̃V�[���̕ۑ�
				GameScene = GAME_SCENE_CHANGE; //��ʐ؂�ւ��V�[���ɕς���
			}
		}

		
		//FPS�l��`��
		FPSDraw();

		//FPS�l��҂�
		FPSWait();

		ScreenFlip();	//�_�u���o�b�t�@�����O������ʂ�`��
	}

	
	

	DxLib_End();						// �c�w���C�u�����g�p�̏I������

	return 0;							// �\�t�g�̏I�� 
}

/// <summary>
/// �Q�[���̃f�[�^��ǂݍ���
/// </summary>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL GameLoad(VOID)
{
	
	
	return TRUE; //���ׂēǂݍ��߂��I

}

/// <summary>
/// �摜���������ɓǂݍ���
/// </summary>
/// <param name="image">�摜�\���̂̃A�h���X</param>
/// <param name="path">�摜�̃p�X</param>
BOOL LoadImageMem(IMAGE* image, const char* path)
{
	strcpyDx(image->path, path); //�p�X�̃R�s�[
	image->handle = LoadGraph(image->path); //�摜�̓ǂݍ���

	//�摜���ǂݍ��߂Ȃ������Ƃ��́A�G���[(�|1)������
	if (image->handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),
			image->path,
			"�摜�ǂݍ��݃G���[!",
			MB_OK
		);

		return FALSE; //�ǂݍ��ݎ��s
	}

	//�摜�̕��ƍ������擾
	GetGraphSize(image->handle, &image->width, &image->height);

	//�ǂݍ��߂�
	return TRUE;
}

/// <summary>
/// ���y���������ɓǂݍ���
/// </summary>
/// <param name="audio">Audio�\���̕ϐ��̃A�h���X</param>
/// <param name="path">Audio�̉��y�p�X</param>
/// <param name="volume">�{�����[��</param>
/// <param name="playType">DX_PLAYTYPE_LOOP or DX_PLAYTYPE_BACK</param>
/// <returns></returns>
BOOL LoadAudio(AUDIO* audio, const char* path, int volume, int playType)
{
	//���y�̓ǂݍ���
	strcpyDx(audio->path, path); //�p�X�̃R�s�[
	audio->handle = LoadSoundMem(audio->path); //���y�̓ǂݍ���

	//�摜���ǂݍ��߂Ȃ������Ƃ��́A�G���[(�|1)������
	if (audio->handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),
			audio->path,
			"�摜�ǂݍ��݃G���[!",
			MB_OK
		);

		return FALSE; //�ǂݍ��ݎ��s
	}

	audio->playType = playType;	
	audio->Volume = volume;
}

/// <summary>
/// �Q�[���̃f�[�^�̏�����
/// </summary>
/// <param name=""></param>
VOID GameInit(VOID)
{
	

}

	/// <summary>
	/// �V�[����؂�ւ���֐�
	/// </summary>
	/// <param name="scene">�V�[��</param>
	VOID ChangeScene(GAME_SCENE scene)
	{
		GameScene = scene; //�V�[����؂�ւ�
		IsFadeIn = FALSE;  //�t�F�[�h�C�����Ȃ�
		IsFadeOut = TRUE;  //�t�F�[�h�A�E�g����
}

	/// <summary>
	/// �^�C�g�����
	/// </summary>
	VOID Title(VOID)
	{
		TitleProc();	//����
		TitleDraw();	//�`��

		return;
	}

	/// <summary>
	/// �^�C�g����ʂ̏���
	/// </summary>
	VOID TitleProc(VOID)
	{
		if (KeyClick(KEY_INPUT_RETURN) == TRUE)
		{
			
			//�V�[���؂�ւ�
			//�v���C��ʂɐ؂�ւ�

			//�Q�[���̏�����
			GameInit();

			ChangeScene(GAME_SCENE_PLAY);

			return;
		}

		

		return;
	}

	/// <summary>
	/// �^�C�g����ʂ̕`��
	/// </summary>
	VOID TitleDraw(VOID)
	{

		
		DrawString(0, 0, "�^�C�g�����", GetColor(0, 0, 0));
		return;
	}

	/// <summary>
		/// �v���C���
		/// </summary>
	VOID Play(VOID)
	{
		PlayProc();	//����
		PlayDraw();	//�`��

		return;
	}

	/// <summary>
	/// �v���C��ʂ̏���
	/// </summary>
	VOID PlayProc(VOID)
	{
		if (KeyClick(KEY_INPUT_RETURN) == TRUE)
		{
			//�V�[���؂�ւ�
			//�G���h��ʂɐ؂�ւ�
			ChangeScene(GAME_SCENE_END);
		}
		

		

		return;
	}

	/// <summary>
	/// �v���C��ʂ̕`��
	/// </summary>
	VOID PlayDraw(VOID)
	{
		


		DrawString(0, 0, "�v���C���", GetColor(0, 0, 0));
		return;
	}

	/// <summary>
	/// �G���h���
	/// </summary>
	VOID End(VOID)
	{
		EndProc();	//����
		EndDraw();	//�`��

		return;
	}

	/// <summary>
	/// �G���h��ʂ̏���
	/// </summary>
	VOID EndProc(VOID)
	{
		if (KeyClick(KEY_INPUT_RETURN) == TRUE)
		{
			
			
			//�V�[���؂�ւ�
			//�^�C�g����ʂɐ؂�ւ�
			ChangeScene(GAME_SCENE_TITLE);
		}
		
		
		return;
	}

	/// <summary>
	/// �G���h��ʂ̕`��
	/// </summary>
	VOID EndDraw(VOID)
	{

		
		DrawString(0, 0, "�G���h���", GetColor(0, 0, 0));		
		return;
	}

	/// <summary>
	/// �؂�ւ����
	/// </summary>
	VOID Change(VOID)
	{
		ChangeProc();	//����
		ChangeDraw();	//�`��

		return;
	}

	/// <summary>
	/// �؂�ւ���ʂ̏���
	/// </summary>
	VOID ChangeProc(VOID)
	{
		
		//�t�F�[�h�C��
		if (IsFadeIn == TRUE)
		{
			if (fadeInCnt > fadeInCntMax)
			{
				fadeInCnt--;	//�J�E���^�����炷
			}
			else
			{
				fadeInCnt = fadeInCntInit;	//�J�E���^������
				IsFadeIn = FALSE;			//�t�F�[�h�C�������I��
			}
		}

		//�t�F�[�h�A�E�g
		if (IsFadeOut == TRUE)
		{
			if (fadeOutCnt < fadeOutCntMax)
			{
				fadeOutCnt++;	//�J�E���^�𑝂₷
			}
			else
			{
				fadeOutCnt = fadeOutCntInit;	//�J�E���^������
				IsFadeOut = FALSE;				//�t�F�[�h�A�E�g�����I��
			}
		}

		//�؂�ւ������I��
		if (IsFadeIn == FALSE && IsFadeOut == FALSE)
		{
			//�t�F�[�h�C���A�t�F�[�h�A�E�g�����Ă��Ȃ��Ƃ�
			GameScene = NextGameScene; //���̃Q�[���V�[���ɐ؂�ւ�
			OldGameScene = GameScene;  //�ȑO�̃Q�[���V�[�����X�V
		}
		return;

		
	}

	/// <summary>
	/// �؂�ւ���ʂ̕`��
	/// </summary>
	VOID ChangeDraw(VOID)
	{
		//�ȑO�̃V�[����`��
		switch (OldGameScene)
		{
		case GAME_SCENE_TITLE:
			TitleDraw();	//�^�C�g����ʂ̕`��
			break;
		case GAME_SCENE_PLAY:
			PlayDraw();		//�v���C��ʂ̕`��
			break;
		case GAME_SCENE_END:
			EndDraw();		//�G���h��ʂ̕`��
			break;
		default:
			break;
		}

		//�t�F�[�h�C��
		if (IsFadeIn == TRUE)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeInCnt / fadeInCntMax) * 255);  //0�`255�܂�
		}

		//�t�F�[�h�A�E�g
		if (IsFadeOut == TRUE)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeOutCnt / fadeOutCntMax) * 255);  //0�`255�܂�
		}

		//�l�p��`��
		DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);
		//�������I��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		
		DrawString(0, 0, "�؂�ւ����", GetColor(0, 0, 0));
		return;
	}


	/// <summary>
	/// �����蔻��̗̈�X�V
	/// </summary>
	/// <param name="chara">�����蔻��̗̈�</param>
	VOID CollUpdatePlayer(CHARACTOR* chara) 
	{
		chara->coll.left = chara->img.x + 120;
		chara->coll.top = chara->img.y;
		chara->coll.right = chara->img.x + chara->img.width;
		chara->coll.bottom = chara->img.y + chara->img.height;

		return;
	}

	/// <summary>
	/// �����蔻��̗̈�X�V
	/// </summary>
	/// <param name="chara">�����蔻��̗̈�</param>
	VOID CollUpdate(CHARACTOR* chara)
	{
		chara->coll.left = chara->img.x;
		chara->coll.top = chara->img.y;
		chara->coll.right = chara->img.x + chara->img.width;
		chara->coll.bottom = chara->img.y + chara->img.height;

		return;
	}

	/// <summary>
	/// ��`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="">��`A</param>
	/// <param name="">��`B</param>
	/// <returns>����������TRUE/������Ȃ��Ȃ�FALSE</returns>
	BOOL OnCollRECT(RECT a,RECT b)
	{
		if (a.left < b.right &&		//��`A�̍���X�̍��W < ��`B�̉E��Y�̍��W�@����
			a.right > b.left &&		//��`A�̉E��X�̍��W > ��`B�̍���Y�̍��W�@����
			a.top < b.bottom &&		//��`A�̏��Y�̍��W < ��`B�̉���Y�̍��W�@����
			a.bottom > b.top		//��`A�̉���Y�̍��W < ��`B�̏��Y�̍��W
			)
		{
			//�������Ă���Ƃ�
			return TRUE;
		}
		else
		{
			//�������Ă��Ȃ��Ƃ�
			return FALSE;
		}
	}
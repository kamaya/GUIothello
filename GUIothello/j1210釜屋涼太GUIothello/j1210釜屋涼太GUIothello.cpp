/*******************************************************************

�I�Z�� �v���O�����@GUI�֌W�t�@�C���@�@�@GUIothello.cpp

���]�H�ƍ������w�Z�@���H�w�ȁ@�y�����@���{�@��
�Q�[���v���O���~���O�@���Ɨp

*******************************************************************/

#include "DxLib.h"
#include "othello.h"

int d = 50;//�}�X�̊Ԋu
int r = d / 2 - 2;//�΂̔��a
int sx = 20, sy = 20;//�Ս���̍��W
int ex = sx + d * SIDE;//�ՉE����x���W
int ey = sy + d * SIDE;//�ՉE����y���W
int rx = ex + 10;//��ʉE�@���ʂȂǕ\�����邽�߂̏ꏊ�����W
int STRCOLOR = GetColor( 0, 0, 200 );//�����F
int STRFONTSIZE = 32;//�����t�H���g�T�C�Y

//�}�E�X�̍��W����I�Z���̍��W�ɕϊ�����֐�
int GetPosfromMouse(int MouseX, int MouseY)
{
	return getposition((MouseX - sx) / d + 1, (MouseY - sy) / d + 1);
}
// GUI�p��manPlayer�֐�
void manPlayerGUI()
{
	//���͂������A���@�肩�`�F�b�N

	int MouseX, MouseY, num, move;
	Move moves[MOVENUM];
	num = generateMoves( moves );
	// ���@�肪�����ꍇ
	if(num == 0)
	{
		nextmove = PASSMOVE;
		return;
	}
	do
	{
		while( (GetMouseInput() & MOUSE_INPUT_LEFT) == 0){
            if(ProcessMessage() == -1){
                DxLib_End();
                exit(1);
            }
            GetMousePoint( &MouseX, &MouseY );
            move = GetPosfromMouse(MouseX,MouseY);
        }
        if( isLegalMove(move) ) {
            nextmove = move;
            break;
        }
	}while(1);

	//return (Move)move;
}

// ��ʕ`��֐��@** �v�ύX�I�I**
void ShowBoard()
{
	int color;
	int x, y, stone;
	int ry = 40, rdy = STRFONTSIZE + 5;
	static int GrHandle = LoadGraph( "back.bmp" );//�w�i�摜�o�^ 640x480
	DrawGraph( 0 , 0 , GrHandle , FALSE );//�w�i��`��
	SetFontSize( STRFONTSIZE ) ;
	DrawBox( sx, sy, ex, ey, GetColor( 0, 255, 0 ), TRUE );//�΂̔Ղ�`��

	for ( y = 1; y <= SIDE; y++ )
	{
		for ( x = 1; x <= SIDE; x++ )
		{
			//��������g�̕`��
			//�����ł͏����Ȏl�p�`���������񏑂��Ă��邪�A�ʂ̃��[�v�Œ������������Ă��������ǂ�
			DrawBox( sx+d*(x-1), sy+d*(y-1), sx+d*x, sy+d*y, GetColor( 0, 0, 0 ), FALSE);
			//��������΂̕`��
			stone = board[getposition(x,y)];//�΂̐F�𒲂ׂ�
			if ( stone == 0 )
				continue;
			if ( stone == B )
				color = GetColor( 0, 0, 0 );//��
			else
				color = GetColor( 255, 255, 255 );//��
			DrawCircle( d/2+sx+d*(x-1), d/2+sy+d*(y-1), r, color, TRUE);//�~�Ő΂�`��
		}
	}
	DrawFormatString( rx, ry, GetColor( 0, 0, 0 ),"��: %d", stonenum[BLACK_TURN] );
	ry += rdy;
	DrawFormatString( rx, ry, GetColor(  255, 255, 255 ),"��: %d", stonenum[WHITE_TURN]);
	ry += rdy * 2;
	DrawFormatString( rx, ry, STRCOLOR,"%d ��", ply );
}


// WinMain�֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow )
{
	int manturn = BLACK_TURN;
	// �^�C�g���� �ύX
	SetMainWindowText( "�I�Z�����{ by ���{" ) ;
	// �E�C���h�E���[�h�ɕύX
	ChangeWindowMode( TRUE ) ;
	// �c�w���C�u��������������
	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
		return -1 ;			// �G���[���N�����璼���ɏI��
	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag( TRUE ) ;

	init();
	ShowBoard();
	SetFontSize( 64 ) ;
	DrawString( 80 , ey / 2 - 20, "Push Space Key!!", STRCOLOR );

	// �X�y�[�X�{�^�����������܂őҋ@
	while( !CheckHitKey( KEY_INPUT_SPACE ) )
	{
		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if( ProcessMessage() == -1 )
			break;		// �G���[���N�����烋�[�v�𔲂���
	}

	ShowBoard();
	SetFontSize( 32 ) ;
	DrawString( rx , ey / 2 - 20, "GAME START!!", STRCOLOR );
	WaitTimer(2000);

	ShowBoard();

	// �΋ǃ��C�����[�v
	while ( !CheckHitKey( KEY_INPUT_ESCAPE ) )//ESC�ŃQ�[���I��
	{

		int num, result;
		Move moves[MOVENUM];
		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if( ProcessMessage() == -1 )
			break ;		// �G���[���N�����烋�[�v�𔲂���
		num = generateMoves( moves );
		if ( num == 0 && isTerminalNode(true))//�I�ǂ��`�F�b�N
		{
			SetFontSize( 32 ) ;
			//�΂̐��ŏ����������肵�\��
			result = stonenum[BLACK_TURN] - stonenum[WHITE_TURN];//����Ȋ�����
			// result �ɂ��\����ς���
			if ( result == 0 )
				DrawString( rx , ey / 2 - 20, "DRAW!!", STRCOLOR );
			else 
				DrawFormatString( rx , ey / 2 - 20, STRCOLOR, "%s WIN!!", ( result > 0 ? "BLACK": "WHITE") );
			break;
		}
		if ( turn == manturn )
				manPlayerGUI();
			//randplayer();
		else
			comPlayer();
		makeMove( nextmove, 0 );
		if( nextmove == PASSMOVE)
			DrawString( rx , ey / 2 - 20, "PASS!!", STRCOLOR );
		else
			ply++;
		ShowBoard();
		WaitTimer(100);
	}
	DrawString( rx , ey / 2 + 50, "Push ANY Key!!", STRCOLOR );
	while( !CheckHitKeyAll())
	{
		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if( ProcessMessage() == -1 )
			break ;		// �G���[���N�����烋�[�v�𔲂���
	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������
	return 0 ;				// �\�t�g�̏I�� 
}
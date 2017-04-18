// player2.h: player 2 agent.
// Author:    Christine JOrdan
// Date:	  <3/14/16>
// MS Visual C++
#ifndef PLAYER1_H
#define PLAYER1_H

class Player1 : public Player
{
private:
	bool human;
	struct Stone
	{
		unsigned short x;
		unsigned short y;
	};
	State state;
	Stone myPieces[4];
	Stone opposingPieces[4];
	Stone movingStone;

public:
	void GetMyGamePieces(board game_board, unsigned short p);
	void GetOpponentGamePieces(board game_board, unsigned short p);

	Move get_move(unsigned short p, board game_board);
	Move MakeMove(Move &m, board b);
	Move RandomMove(Move &m, board b);
	Move FourCornersBlock(Move &m, board b);
	Move VerticalBlock(Move& m, board b);
	Move HorizontalBlock(Move &m, board b);
	Move ClusterBlock(Move &m, board b);

	bool isValid(Move move, board game_board);
	bool IsBoxing(Move m, board b);
	bool IsClusterWin(Stone s, board b, Move &m);
	bool IsFourCornersWin(Move &m, board b);
	bool IsFourCornersLoss(Move m, board b);
	bool IsHorizontalWin(Move &m, board b);
	bool IsHorizontalLoss(Move m, board b);
	bool IsVerticalWin(Move &m, board b);
	bool IsVerticalLoss(Move &m, board b);
};

Move Player1::get_move(unsigned short p, board game_board)
{
	Move move;

	move.player = p;

	if (human)
	{
		cout << "Enter move (old_x old_y new_x new_y): ";
		cin >> move.src_x;
		cin >> move.src_y;
		cin >> move.dst_x;
		cin >> move.dst_y;
	}
	else
	{
		//we need to locate the stones for this player
		GetMyGamePieces(game_board, p);
		GetOpponentGamePieces(game_board, p);
		//construct the move for this player
		move = MakeMove(move, game_board);

	}

	return move;
}

//calls all the functions to construct a move from the current state of
//the game
Move Player1::MakeMove(Move &m, board b)
{
	//check losing conditions and if we need/can block oppenent
	if (IsFourCornersWin(m, b))
		return m;
	if (IsHorizontalWin(m, b))
		return m;
	if (IsVerticalWin(m, b))
		return m;

	if (IsFourCornersLoss(m, b))
		return FourCornersBlock(m, b);
	if (IsHorizontalLoss(m, b))
		return HorizontalBlock(m, b);
	if (IsVerticalLoss(m, b))
		return VerticalBlock(m, b);


	return RandomMove(m, b);

	/*m.src_x = 2;
	m.src_y = 2;
	m.dst_x = 2;
	m.dst_y = 1;
	do
	{
	if (isValid(m, b) && !IsBoxing(m, b))
	return m;
	} while (true);

	return m;*/
}

//retrieves the player's stones and stores them in an array for easier access
//currently sets a random stone to moving stone as well
void Player1::GetMyGamePieces(board game_board, unsigned short p)
{
	int index = 0;

	for (unsigned short i = 0; i < XYDIM; ++i)
	{
		for (unsigned short j = 0; j < XYDIM; ++j)
		{
			if (game_board.layout[j][i] == p)
			{
				myPieces[index].x = i;
				myPieces[index].y = j;
				++index;
			}
		}
	}
}

void Player1::GetOpponentGamePieces(board game_board, unsigned short p)
{
	int index = 0;

	for (unsigned short i = 0; i < XYDIM; ++i)
	{
		for (unsigned short j = 0; j < XYDIM; ++j)
		{
			if (game_board.layout[j][i] != p && game_board.layout[j][i] != EMPTY)
			{
				opposingPieces[index].x = i;
				opposingPieces[index].y = j;
				++index;
			}
		}
	}
}

//this is the random move function
Move Player1::RandomMove(Move &m, board game_board)
{
	//need to use address of m

	int x, y;
	bool moveComplete = false;
	//int index = 0;
	//s = myPieces[index];

	do
	{
		movingStone = myPieces[rand() % 4];
		m.src_x = movingStone.x;  //set move source
		m.src_y = movingStone.y;
		x = movingStone.x;		//set dummy x & y
		y = movingStone.y;

		int dir = rand() % 8 + 1; //pick a random direction

		switch (dir)
		{
		case 1:
		{
			//move NW
			//to move NW we must decriment y AND decriment x
			//for dst
			while (y >= 0 && y < XYDIM && x >= 0 && x < XYDIM && !moveComplete)
			{
				--y;
				--x;
				m.dst_x = (unsigned short)x;
				m.dst_y = (unsigned short)y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}
		}
		break;

		case 2:
		{
			//move N
			//since we are trying to move N we are incrementing y
			//for a dst and leaving x alone
			while (y >= 0 && y < XYDIM && !moveComplete)
			{
				--y;
				m.dst_x = movingStone.x;
				m.dst_y = (unsigned short)y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}

		}
		break;

		case 3:
		{
			//move NE
			while (y >= 0 && y < XYDIM && x >= 0 && x < XYDIM && !moveComplete)
			{
				--y;
				++x;
				m.dst_x = (unsigned short)x;
				m.dst_y = (unsigned short)y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}

		}
		break;

		case 4:
		{
			//move E
			//since we are trying to move E we are incrementing x
			//for a dst and leaving y alone
			while (x >= 0 && x < XYDIM && !moveComplete)
			{
				++x;
				m.dst_x = (unsigned short)x;
				m.dst_y = movingStone.y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}
		}
		break;

		case 5:
		{
			//move SE
			while (y >= 0 && y < XYDIM && x >= 0 && x < XYDIM && !moveComplete)
			{
				++y;
				++x;
				m.dst_x = (unsigned short)x;
				m.dst_y = (unsigned short)y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}
		}
		break;

		case 6:
		{
			//move S
			//since we are trying to move S we are Decrimenting y
			//for a dst and leaving x alone
			while (y >= 0 && y < XYDIM && !moveComplete)
			{
				++y;
				m.dst_x = movingStone.x;
				m.dst_y = (unsigned short)y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}
		}
		break;

		case 7:
		{
			//move SW
			while (y >= 0 && y < XYDIM && x >= 0 && x < XYDIM && !moveComplete)
			{
				++y;
				--x;
				m.dst_x = (unsigned short)x;
				m.dst_y = (unsigned short)y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}
		}
		break;

		case 8:
		{
			//move W
			//since we are trying to move W we are decrimenting x
			//for a dst and leaving y alone
			while (x >= 0 && x < XYDIM && !moveComplete)
			{
				--x;
				m.dst_x = (unsigned short)x;
				m.dst_y = movingStone.y;

				if (isValid(m, game_board) && !IsBoxing(m, game_board))
					moveComplete = true;
			}
		}
		break;

		default:
		{
			moveComplete = false;
		}break;
		}
	} while (!moveComplete);

	return m;
}

//check for valid move so we don't spam the game board.
bool Player1::isValid(Move move, board game_board)
{
	short x, y;
	//board game_board;
	bool allclear;

	// Get current state of the game.
	//game_board = state.get_game_state();

	// First, verify that a player isn't trying to move another's stone.
	if (move.player != game_board.layout[move.src_y][move.src_x])
		return false;

	// Second, verify that a player actually tries to move somewhere...
	if (move.dst_y == move.src_y && move.dst_x == move.src_x)  // Wow - really?
		return false;

	// Check for invalid 'North' move.
	if (move.dst_y < move.src_y && move.dst_x == move.src_x) {

		y = move.src_y - 1;
		allclear = true;

		while (allclear && y >= 0)
			if (game_board.layout[y][move.dst_x] != EMPTY)
				allclear = false;
			else
				y--;

		y++;	// Went past the valid move cell, so back it up.

		if (move.dst_y != y)
			return false;
	}

	// Check for invalid 'South' move.
	if (move.dst_y > move.src_y && move.dst_x == move.src_x) {

		y = move.src_y + 1;
		allclear = true;

		while (allclear && y < XYDIM)
			if (game_board.layout[y][move.dst_x] != EMPTY)
				allclear = false;
			else
				y++;

		y--;	// Went past the valid move cell, so back it up.

		if (move.dst_y != y)
			return false;
	}

	// Check for invalid 'East' move.
	if (move.dst_y == move.src_y && move.dst_x > move.src_x) {

		x = move.src_x + 1;
		allclear = true;

		while (allclear && x < XYDIM)
			if (game_board.layout[move.dst_y][x] != EMPTY)
				allclear = false;
			else
				x++;

		x--;	// Went past the valid move cell, so back it up.

		if (move.dst_x != x)
			return false;
	}

	// Check for invalid 'West' move.
	if (move.dst_y == move.src_y && move.dst_x < move.src_x) {

		x = move.src_x - 1;
		allclear = true;

		while (allclear && x >= 0)
			if (game_board.layout[move.dst_y][x] != EMPTY)
				allclear = false;
			else
				x--;

		x++;	// Went past the valid move cell, so back it up.

		if (move.dst_x != x)
			return false;
	}

	// Check for invalid 'Northeast' move.
	if (move.dst_y < move.src_y && move.dst_x > move.src_x) {

		x = move.src_x + 1;
		y = move.src_y - 1;
		allclear = true;

		while (allclear && y >= 0 && x < XYDIM)
			if (game_board.layout[y][x] != EMPTY)
				allclear = false;
			else {
				x++;
				y--;
			}

			x--;	// Went past the valid move cell, so back it up.
			y++;

			if (move.dst_x != x || move.dst_y != y)
				return false;
	}

	// Check for invalid 'Northwest' move.
	if (move.dst_y < move.src_y && move.dst_x < move.src_x) {

		x = move.src_x - 1;
		y = move.src_y - 1;
		allclear = true;

		while (allclear && y >= 0 && x >= 0)	// Fix due to Kirt Guthrie.
			if (game_board.layout[y][x] != EMPTY)
				allclear = false;
			else
			{
				x--;
				y--;
			}

		x++;	// Went past the valid move cell, so back it up.
		y++;

		if (move.dst_x != x || move.dst_y != y)
			return false;
	}

	// Check for invalid 'Southeast' move.
	if (move.dst_y > move.src_y && move.dst_x > move.src_x) {

		x = move.src_x + 1;
		y = move.src_y + 1;
		allclear = true;

		while (allclear && y < XYDIM && x < XYDIM)
			if (game_board.layout[y][x] != EMPTY)
				allclear = false;
			else {
				x++;
				y++;
			}

			x--;	// Went past the valid move cell, so back it up.
			y--;

			if (move.dst_x != x || move.dst_y != y)
				return false;
	}

	// Check for invalid 'Southwest' move.
	if (move.dst_y > move.src_y && move.dst_x < move.src_x) {

		x = move.src_x - 1;
		y = move.src_y + 1;
		allclear = true;

		while (allclear && y < XYDIM && x >= 0)
			if (game_board.layout[y][x] != EMPTY)
				allclear = false;
			else {
				x--;
				y++;
			}

			x++;	// Went past the valid move cell, so back it up.
			y--;

			if (move.dst_x != x || move.dst_y != y)
				return false;
	}

	return true;   // Made it past all the checks - Valid move!
}

//checks for a losing move
//still buggy
bool Player1::IsBoxing(Move m, board b)
{
	//checks for boxing in upper left (0,0)
	if ((b.layout[0][0] != m.player && b.layout[0][0] != EMPTY))
	{
		//checks for player's pieces around the corner
		//checking if a move to (1,0) will lose the game
		if ((b.layout[1][0] == m.player && b.layout[1][1] == m.player) &&
			(m.dst_x == 1 && m.dst_y == 0))
			return true;
		//checking if a move to (1,1) will lose the game
		if ((b.layout[1][0] == m.player && b.layout[0][1] == m.player) &&
			(m.dst_x == 1 && m.dst_y == 1))
			return true;
		//checking if a move to (0, 1) will lose the game
		if ((b.layout[1][1] == m.player && b.layout[0][1] == m.player) &&
			(m.dst_x == 0 && m.dst_y == 1))
			return true;
	}
	//check for boxing in upper right corner (3,0)
	if ((b.layout[0][3] != m.player && b.layout[0][3] != EMPTY))
	{
		//checks for player's pieces around the corner
		//checking if a move to (2, 0) will lose the game
		if (b.layout[1][2] == m.player && b.layout[1][3] == m.player &&
			(m.dst_x == 2 && m.dst_y == 0))
			return true;
		//checking if a move to (2,1) will lose the game
		if (b.layout[0][2] == m.player && b.layout[1][3] == m.player &&
			(m.dst_x == 2 && m.dst_y == 1))
			return true;
		//checking if a move to (3,1) will lose the game
		if (b.layout[1][2] == m.player && b.layout[0][2] == m.player &&
			(m.dst_x == 3 && m.dst_y == 1))
			return true;
	}
	//check for boxing in lower left corner (0,3)
	if ((b.layout[3][0] != m.player && b.layout[3][0] != EMPTY))
	{
		//checks for player's pieces around the corner
		//checking if a move to (0,2) will lose the game
		if (b.layout[2][1] == m.player && b.layout[3][1] == m.player &&
			(m.dst_x == 0 && m.dst_y == 2))
			return true;
		//checking if a move to ((1,2) will lose the game
		if (b.layout[2][0] == m.player && b.layout[3][1] == m.player &&
			(m.dst_x == 1 && m.dst_y == 2))
			return true;
		//checking if a move to (2,3) will lose the game
		if (b.layout[2][0] == m.player && b.layout[2][1] == m.player &&
			(m.dst_x == 1 && m.dst_y == 3))
			return true;
	}
	//check for boxing in lower right corner (3,3)
	if ((b.layout[3][3] != m.player && b.layout[3][3] != EMPTY))
	{
		//checks for player's pieces around the corner
		//checking if a move to (2,3) will lose the game
		if (b.layout[3][2] == m.player && b.layout[2][2] == m.player &&
			(m.dst_x == 3 && m.dst_y == 2))
			return true;
		//checking if a move to (2,2) will lose the game
		if (b.layout[3][2] == m.player && b.layout[2][3] == m.player &&
			(m.dst_x == 2 && m.dst_y == 2))
			return true;
		//checking if a move to (3,2) will lose the game
		if (b.layout[2][2] == m.player && b.layout[2][3] == m.player &&
			(m.dst_x == 2 && m.dst_y == 3))
			return true;
	}

	return false;  //returns whether the move is boxing and a losing move
}

//blocks my opponent from winning with four corners if possible
Move Player1::FourCornersBlock(Move &m, board b)
{
	for (int i = 0; i < 4; ++i)
	{
		if (b.layout[0][0] == EMPTY)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;

			m.dst_x = 0;
			m.dst_y = 0;

			if (isValid(m, b))
				return m;
		}
		else if (b.layout[0][3] == EMPTY)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;

			m.dst_x = 3;
			m.dst_y = 0;

			if (isValid(m, b))
				return m;
		}
		else if (b.layout[3][3] == EMPTY)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;

			m.dst_x = 3;
			m.dst_y = 3;

			if (isValid(m, b))
				return m;
		}
		else if (b.layout[3][0] == EMPTY)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;

			m.dst_x = 0;
			m.dst_y = 3;

			if (isValid(m, b))
				return m;
		}
	}

	return RandomMove(m, b);
}

//blocks opposing vertical win if possible
Move Player1::VerticalBlock(Move & m, board b)
{
	if (opposingPieces[0].x == opposingPieces[1].x == opposingPieces[2].x)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[0].x;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_y = j;

				if (isValid(m, b))
					return m;
			}
		}
	}
	if (opposingPieces[0].x == opposingPieces[1].x == opposingPieces[3].x)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[0].x;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_y = j;

				if (isValid(m, b))
					return m;
			}
		}
	}
	if (opposingPieces[0].x == opposingPieces[2].x == opposingPieces[3].x)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[0].x;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_y = j;

				if (isValid(m, b))
					return m;
			}
		}
	}
	if (opposingPieces[1].x == opposingPieces[2].x == opposingPieces[3].x)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[1].x;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_y = j;

				if (isValid(m, b))
					return m;
			}
		}
	}

	return RandomMove(m, b);
}

//blocks opposing vertical win if possible
Move Player1::HorizontalBlock(Move & m, board b)
{
	if (opposingPieces[0].y == opposingPieces[1].y == opposingPieces[2].y)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[0].y;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_x = j;

				if (isValid(m, b))
					return m;
			}
		}
	}
	if (opposingPieces[0].y == opposingPieces[1].y == opposingPieces[3].y)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[0].y;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_x = j;

				if (isValid(m, b))
					return m;
			}
		}
	}
	if (opposingPieces[0].y == opposingPieces[2].y == opposingPieces[3].y)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[0].y;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_x = j;

				if (isValid(m, b))
					return m;
			}
		}
	}
	if (opposingPieces[1].y == opposingPieces[2].y == opposingPieces[3].y)
	{
		for (int i = 0; i < 4; ++i)
		{
			m.src_x = myPieces[i].x;
			m.src_y = myPieces[i].y;
			m.dst_x = opposingPieces[1].y;

			for (int j = 0; j < 4; ++j)
			{
				m.dst_x = j;

				if (isValid(m, b))
					return m;
			}
		}
	}

	return RandomMove(m, b);
}

//???
Move Player1::ClusterBlock(Move & m, board b)
{
	return Move();
}

//???
bool Player1::IsClusterWin(Stone s, board b, Move &m)
{
	//if there is a ready to win cluster in a valid move eg
	//  XX  XX   X    X
	//  X    X  XX   XX
	//then take that move else move normally

	bool isCluster = false;
	int i = 0;

	do
	{
		return false;
	} while (!isCluster || i < 4);

	return false;
}

//checks if I can win by four in a row horizontaly and moves
bool Player1::IsHorizontalWin(Move & m, board b)
{
	//set of four checks first row
	if (b.layout[0][0] == b.layout[0][1] == b.layout[0][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 2 && myPieces[i].y != 0))
			{
				m.dst_x = 3;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;

				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][0] == b.layout[0][1] == b.layout[0][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 0))
			{
				m.dst_x = 2;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][0] == b.layout[0][2] == b.layout[0][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 0) &&
				(myPieces[i].x != 2 && myPieces[i].y != 0))
			{
				m.dst_x = 1;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][3] == b.layout[0][1] == b.layout[0][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 2 && myPieces[i].y != 0))
			{
				m.dst_x = 0;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	//checks second row
	if (b.layout[1][0] == b.layout[1][1] == b.layout[1][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 1) &&
				(myPieces[i].x != 1 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1))
			{
				m.dst_x = 3;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;

				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[1][0] == b.layout[1][1] == b.layout[1][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 1) &&
				(myPieces[i].x != 1 && myPieces[i].y != 1) &&
				(myPieces[i].x != 3 && myPieces[i].y != 1))
			{
				m.dst_x = 2;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[1][0] == b.layout[1][2] == b.layout[1][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 1) &&
				(myPieces[i].x != 3 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1))
			{
				m.dst_x = 1;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[1][3] == b.layout[1][1] == b.layout[1][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 1) &&
				(myPieces[i].x != 1 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1))
			{
				m.dst_x = 0;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	//checks third row
	if (b.layout[2][0] == b.layout[2][1] == b.layout[2][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 2) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2) &&
				(myPieces[i].x != 2 && myPieces[i].y != 2))
			{
				m.dst_x = 3;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;

				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[2][0] == b.layout[2][1] == b.layout[2][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 2) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2) &&
				(myPieces[i].x != 3 && myPieces[i].y != 2))
			{
				m.dst_x = 2;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[2][0] == b.layout[2][2] == b.layout[2][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 2) &&
				(myPieces[i].x != 3 && myPieces[i].y != 2) &&
				(myPieces[i].x != 2 && myPieces[i].y != 2))
			{
				m.dst_x = 1;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[2][3] == b.layout[2][1] == b.layout[2][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 2) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2) &&
				(myPieces[i].x != 2 && myPieces[i].y != 2))
			{
				m.dst_x = 0;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	//checks last row
	if (b.layout[3][0] == b.layout[3][1] == b.layout[3][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 1 && myPieces[i].y != 3) &&
				(myPieces[i].x != 2 && myPieces[i].y != 3))
			{
				m.dst_x = 3;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;

				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][0] == b.layout[3][1] == b.layout[3][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 1 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3))
			{
				m.dst_x = 2;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][0] == b.layout[3][2] == b.layout[3][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3) &&
				(myPieces[i].x != 2 && myPieces[i].y != 3))
			{
				m.dst_x = 1;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][3] == b.layout[3][1] == b.layout[3][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 2) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2) &&
				(myPieces[i].x != 2 && myPieces[i].y != 2))
			{
				m.dst_x = 0;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	return false;
}

//checks if I can lose by horizontal four in a row next turn
bool Player1::IsHorizontalLoss(Move m, board b)
{
	if (opposingPieces[0].y == opposingPieces[1].y == opposingPieces[2].y)
		return true;
	if (opposingPieces[0].y == opposingPieces[1].y == opposingPieces[3].y)
		return true;
	if (opposingPieces[0].y == opposingPieces[2].y == opposingPieces[3].y)
		return true;
	if (opposingPieces[1].y == opposingPieces[2].y == opposingPieces[3].y)
		return true;
	return false;
}

//checks if I can win by vertical four in a row
bool Player1::IsVerticalWin(Move & m, board b)
{
	//set of four checks first column
	if (b.layout[0][0] == b.layout[1][0] == b.layout[2][0] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 0 && myPieces[i].y != 1) &&
				(myPieces[i].x != 0 && myPieces[i].y != 2))
			{
				m.dst_x = 0;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][0] == b.layout[1][0] == b.layout[3][0] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 0 && myPieces[i].y != 1) &&
				(myPieces[i].x != 0 && myPieces[i].y != 3))
			{
				m.dst_x = 0;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][0] == b.layout[2][0] == b.layout[3][0] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 0 && myPieces[i].y != 2))
			{
				m.dst_x = 0;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][0] == b.layout[1][0] == b.layout[2][0] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 0 && myPieces[i].y != 1) &&
				(myPieces[i].x != 0 && myPieces[i].y != 2))
			{
				m.dst_x = 0;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	//checks second column
	if (b.layout[0][1] == b.layout[1][1] == b.layout[2][1] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 1) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2))
			{
				m.dst_x = 1;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][1] == b.layout[1][1] == b.layout[3][1] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 1) &&
				(myPieces[i].x != 1 && myPieces[i].y != 3))
			{
				m.dst_x = 1;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][1] == b.layout[2][1] == b.layout[3][1] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 3) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2))
			{
				m.dst_x = 1;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][1] == b.layout[1][1] == b.layout[2][1] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 1 && myPieces[i].y != 0) &&
				(myPieces[i].x != 1 && myPieces[i].y != 3) &&
				(myPieces[i].x != 1 && myPieces[i].y != 2))
			{
				m.dst_x = 1;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	//checks third column
	if (b.layout[0][2] == b.layout[1][2] == b.layout[2][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 2 && myPieces[i].y != 0) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 2))
			{
				m.dst_x = 2;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][2] == b.layout[1][2] == b.layout[3][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 2 && myPieces[i].y != 0) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 3))
			{
				m.dst_x = 2;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][2] == b.layout[2][2] == b.layout[3][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 2 && myPieces[i].y != 0) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 3))
			{
				m.dst_x = 2;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;

				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][2] == b.layout[1][2] == b.layout[2][2] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 2 && myPieces[i].y != 3) &&
				(myPieces[i].x != 2 && myPieces[i].y != 1) &&
				(myPieces[i].x != 2 && myPieces[i].y != 2))
			{
				m.dst_x = 2;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	//checks last column
	if (b.layout[0][3] == b.layout[1][3] == b.layout[2][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 1) &&
				(myPieces[i].x != 3 && myPieces[i].y != 2))
			{
				m.dst_x = 3;
				m.dst_y = 3;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][3] == b.layout[1][3] == b.layout[3][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 1) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3))
			{
				m.dst_x = 3;
				m.dst_y = 2;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[0][3] == b.layout[2][3] == b.layout[3][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 2))
			{
				m.dst_x = 3;
				m.dst_y = 1;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}
	if (b.layout[3][3] == b.layout[1][3] == b.layout[2][3] == m.player)
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 3 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 1) &&
				(myPieces[i].x != 3 && myPieces[i].y != 2))
			{
				m.dst_x = 3;
				m.dst_y = 0;
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				if (isValid(m, b))
					return true;
			}
		}
	}

	return false;
}

//checks if I can lose by Vertical four in a row next turn
bool Player1::IsVerticalLoss(Move & m, board b)
{
	if (opposingPieces[0].x == opposingPieces[1].x == opposingPieces[2].x)
		return true;
	if (opposingPieces[0].x == opposingPieces[1].x == opposingPieces[3].x)
		return true;
	if (opposingPieces[0].x == opposingPieces[2].x == opposingPieces[3].x)
		return true;
	if (opposingPieces[1].x == opposingPieces[2].x == opposingPieces[3].x)
		return true;
	return false;
}

//is "four corners" win possible
bool Player1::IsFourCornersWin(Move &m, board b)
{
	if ((b.layout[0][0] == m.player && b.layout[3][0] == m.player &&
		b.layout[0][3] == m.player && b.layout[3][3] == 0))
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 0))
			{
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				m.dst_x = 3;
				m.dst_y = 3;

				//check if move to (0, 3) is valid and thus win the game
				if (isValid(m, b))
					return true;
			}
		}
	}

	if ((b.layout[0][0] == m.player && b.layout[3][3] == m.player &&
		b.layout[0][3] == m.player && b.layout[3][0] == 0))
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 0))
			{
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				m.dst_x = 0;
				m.dst_y = 3;

				//check if move to (3, 3) is valid and thus win the game
				if (isValid(m, b))
					return true;
			}
		}

	}

	if ((b.layout[0][0] == m.player && b.layout[3][3] == m.player &&
		b.layout[3][0] == m.player && b.layout[0][3] == 0))
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 0) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3) &&
				(myPieces[i].x != 0 && myPieces[i].y != 3))
			{
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				m.dst_x = 3;
				m.dst_y = 0;

				//check if move to (3, 0) is valid and thus win the game
				if (isValid(m, b))
					return true;
			}
		}

	}

	if ((b.layout[3][0] == m.player && b.layout[3][3] == m.player &&
		b.layout[0][3] == m.player && b.layout[0][0] == 0))
	{
		for (int i = 0; i < 4; ++i)
		{
			if ((myPieces[i].x != 0 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 3) &&
				(myPieces[i].x != 3 && myPieces[i].y != 0))
			{
				m.src_x = myPieces[i].x;
				m.src_y = myPieces[i].y;
				m.dst_x = 0;
				m.dst_y = 0;

				//check if move to (3, 3) is valid and thus win the game
				if (isValid(m, b))
					return true;
			}
		}

	}

	return false;
}

//checks for a four corners loss
bool Player1::IsFourCornersLoss(Move m, board b)
{
	if ((b.layout[0][0] != m.player && b.layout[0][0] != 0) &&
		(b.layout[3][0] != m.player && b.layout[3][0] != 0) &&
		(b.layout[0][3] != m.player && b.layout[0][3] != 0) &&
		(b.layout[3][3] == 0))
	{
		return true;
	}
	if ((b.layout[0][0] != m.player && b.layout[0][0] != 0) &&
		(b.layout[3][3] != m.player && b.layout[3][3] != 0) &&
		(b.layout[0][3] != m.player && b.layout[0][3] != 0) &&
		(b.layout[3][0] == 0))
	{
		return true;
	}
	if ((b.layout[0][0] != m.player && b.layout[0][0] != 0) &&
		(b.layout[3][3] != m.player && b.layout[3][3] != 0) &&
		(b.layout[3][0] != m.player && b.layout[3][0] != 0) &&
		(b.layout[0][3] == 0))
	{
		return true;
	}
	if ((b.layout[0][3] != m.player && b.layout[0][3] != 0) &&
		(b.layout[3][3] != m.player && b.layout[3][3] != 0) &&
		(b.layout[3][0] != m.player && b.layout[3][0] != 0) &&
		(b.layout[0][0] == 0))
	{
		return true;
	}

	return false;
}
#endif
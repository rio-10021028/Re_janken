#include <iostream>
#include "janken.h"
using namespace std;

enum RPSHands
{
	ROCK,		// グー   > 0
	SCISSORS,   // チョキ > 1
	PAPER       // パー   > 2
};

enum RPSResults
{
	LOSE,  // 負け > 0
	WIN,   // 勝ち > 1
	TIE    // 分け > 2
};

const char* RPSHandMessage[]
{
	"グー",
	"チョキ",
	"パー",
};

const char* RPSResultsMessage[]
{
	"負け...",
	"勝ち！！",
};

struct Result
{
	int lose;
	int win;
};

static void initRand()
{
	srand((unsigned int)time(nullptr));
}

static RPSHands cpuHand()
{
	int hand = rand() % 3;

	switch (hand)
	{
	case ROCK:
		return ROCK;
	case SCISSORS:
		return SCISSORS;
	case PAPER:
		return PAPER;
	}
}

static RPSResults judgeResult(RPSHands user, RPSHands cpu)
{
	int result = ((user - cpu) + 2) % 3;

	switch (result)
	{
	case LOSE:
		return LOSE;
	case WIN:
		return WIN;
	case TIE:
		return TIE;
	}
}

static RPSResults janken()
{
	RPSHands user = ROCK;
	RPSHands cpu = ROCK;

	RPSResults currentResult = LOSE;

	// あいこならループ
	while (true)
	{
		bool inputFlag = true;

		// 正しい入力までループ
		while (inputFlag)
		{
			int input = 0;
			cout << "グー   > 0" << endl
				<< "チョキ > 1" << endl
				<< "パー   > 2" << endl
				<< "じゃんけん... > " << flush;
			cin >> input;

			switch (input)
			{
			case ROCK:
				user = ROCK;
				inputFlag = false;
				break;
			case SCISSORS:
				user = SCISSORS;
				inputFlag = false;
				break;
			case PAPER:
				user = PAPER;
				inputFlag = false;
				break;
			default:
				cout << "0, 1, 2 を入力してください\n\n";
			}
		}

		// cpuの手決定
		cpu = cpuHand();

		// 手を表示
		cout << "you > " << RPSHandMessage[user] << endl
			<< "cpu > " << RPSHandMessage[cpu] << endl << endl;

		// ジャッジ
		currentResult = judgeResult(user, cpu);

		// あいこじゃなければ結果を返す
		if (currentResult != TIE)
		{
			return currentResult;
		}

		cout << "あいこ！　もう一度！\n\n";
	}
}

void JankenSimurator()
{
	initRand();

	RPSResults currentResult = LOSE;
	int round = 1;
	int num = 0;

	Result result =
	{
		0,
		0,
	};

	// n本か決まるまでループ
	while (true)
	{
		num = 0;

		cout << "じゃんけんゲームへようこそ！" << endl
			<< "何本先取にしますか > " << flush;
		cin >> num;

		if (num <= 0)
		{
			cout << "もう一度入力してください\n\n";
		}
		else if (1 <= num && num <= 10)
		{
			break;
		}
		else
		{
			cout << "ちょっと多いかもな... 10 にしておきますね\n\n";
			num = 10;
			break;
		}
	}

	cout << num << " 本先取！　じゃんけんゲーム！\n\n";

	// n本終わるまでループ
	while (true)
	{
		cout << "===== 第 " << round << " 回戦 =====\n\n";

		// janken呼び出し
		currentResult = janken();

		// 結果
		switch (currentResult)
		{
		case LOSE:
			result.lose++;
			break;
		case WIN:
			result.win++;
		}

		// n本終わったらループ脱出
		if (result.lose == num || result.win == num)
		{
			break;
		}

		// 暫定結果表示
		cout << RPSResultsMessage[currentResult] << endl
			<< "----- 暫定結果 ----- " << endl
			<< "勝ち > " << result.win << endl
			<< "負け > " << result.lose << endl << endl;

		// round数加算
		round++;
	}

	// 最終結果表示
	cout << "===== 最終結果 =====\n\n"
		<< "勝ち > " << result.win << endl
		<< "負け > " << result.lose << endl
		<< "あなたの " << (result.win == 3 ? RPSResultsMessage[WIN] : RPSResultsMessage[LOSE])
		<< endl << endl;

}
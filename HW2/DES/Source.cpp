#include <iostream>
#include <vector>
#include <string>
using namespace std;

//IP置換表
vector<int> IP_tab = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };
//IP-1
vector<int> IP_inverse = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 };
//Expansion
vector<int> E = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };
//S-box
vector<char> S1 = { 'E','4','D','1','2','F','B','8','3','A','6','C','5','9','0','7','0','F','7','4','E','2','D','1','A','6','C','B','9','5','3','8','4','1','E','8','D','6','2','B','F','C','9','7','3','A','5','0','F','C','8','2','4','9','1','7','5','B','3','E','A','0','6','D' };
vector<char> S2 = { 'F','1','8','E','6','B','3','4','9','7','2','D','C','0','5','A','3','D','4','7','F','2','8','E','C','0','1','A','6','9','B','5','0','E','7','B','A','4','D','1','5','8','C','6','9','3','2','F','D','8','A','1','3','F','4','2','B','6','7','C','0','5','E','9' };
vector<char> S3 = { 'A','0','9','E','6','3','F','5','1','D','C','7','B','4','2','8','D','7','0','9','3','4','6','A','2','8','5','E','C','B','F','1','D','6','4','9','8','F','3','0','B','1','2','C','5','A','E','7','1','A','D','0','6','9','8','7','4','F','E','3','B','5','2','C' };
vector<char> S4 = { '7','D','E','3','0','6','9','A','1','2','8','5','B','C','4','F','D','8','B','5','6','F','0','3','4','7','2','C','1','A','E','9','A','6','9','0','C','B','7','D','F','1','3','E','5','2','8','4','3','F','0','6','A','1','D','8','9','4','5','B','C','7','2','E' };
vector<char> S5 = { '2','C','4','1','7','A','B','6','8','5','3','F','D','0','E','9','E','B','2','C','4','7','D','1','5','0','F','A','3','9','8','6','4','2','1','B','A','D','7','8','F','9','C','5','6','3','0','E','B','8','C','7','1','E','2','D','6','F','0','9','A','4','5','3' };
vector<char> S6 = { 'C','1','A','F','9','2','6','8','0','D','3','4','E','7','5','B','A','F','4','2','7','C','9','5','6','1','D','E','0','B','3','8','9','E','F','5','2','8','C','3','7','0','4','A','1','D','B','6','4','3','2','C','9','5','F','A','B','E','1','7','6','0','8','D' };
vector<char> S7 = { '4','B','2','E','F','0','8','D','3','C','9','7','5','A','6','1','D','0','B','7','4','9','1','A','E','3','5','C','2','F','8','6','1','4','B','D','C','3','7','E','A','F','6','8','0','5','9','2','6','B','D','8','1','4','A','7','9','5','0','F','E','2','3','C' };
vector<char> S8 = { 'D','2','8','4','6','F','B','1','A','9','3','E','5','0','C','7','1','F','D','8','A','3','7','4','C','5','6','B','0','E','9','2','7','B','4','1','9','C','E','2','0','6','A','D','F','3','5','8','2','1','E','7','4','A','8','D','F','C','9','0','3','5','6','B' };

//Permutation
vector<int> P = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
//keyto56
vector<int> PC_1 = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
//keyto48
vector<int> PC_2 = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };

string fourbits(char in)//每個字轉成4位元
{
	switch (in)
	{
	case '0':return "0000";
	case '1':return "0001";
	case '2':return "0010";
	case '3':return "0011";
	case '4':return "0100";
	case '5':return "0101";
	case '6':return "0110";
	case '7':return "0111";
	case '8':return "1000";
	case '9':return "1001";
	case 'A':return "1010";
	case 'B':return "1011";
	case 'C':return "1100";
	case 'D':return "1101";
	case 'E':return "1110";
	case 'F':return "1111";
	default:
		break;
	}
}
char fourbit_inv(string input)//將4位元轉回字
{
	if (input == "0000")
		return '0';
	else if (input == "0001")
		return '1';
	else if (input == "0010")
		return '2';
	else if (input == "0011")
		return '3';
	else if (input == "0100")
		return '4';
	else if (input == "0101")
		return '5';
	else if (input == "0110")
		return '6';
	else if (input == "0111")
		return '7';
	else if (input == "1000")
		return '8';
	else if (input == "1001")
		return '9';
	else if (input == "1010")
		return 'A';
	else if (input == "1011")
		return 'B';
	else if (input == "1100")
		return 'C';
	else if (input == "1101")
		return 'D';
	else if (input == "1110")
		return 'E';
	else if (input == "1111")
		return 'F';
}
string LS(string input, int num)//左移
{
	string put = "";
	for (int i = num; i < input.length() + num; i++)
	{
		if (i >= input.length())
		{
			put += input[i - input.length()];
		}
		else
		{
			put += input[i];
		}
	}
	return put;
}

string RS(string input, int num)//右移
{
	string put = "";
	for (int i = input.length() - num; i < input.length(); i++)
	{
		put += input[i];
	}
	for (int i = 0; i < input.length() - num; i++)
	{
		put += input[i];
	}
	return put;
}

int main()
{
	string input;//./EncryptDES
	while (cin >> input)
	{
		if (input == "./EncryptDES")
		{
			string keys;//金鑰16進制
			string keys_56;//56位元key
			string keys_L = "";
			string keys_R = "";
			string plaintext;//原文16進制
			string plaintext_L = "";
			string plaintext_R = "";
			string keys_64 = "";//Key64位元
			string plaintext_64 = "";//原文64位元
			string ciphertext = "0x";//結果
			string result_64 = "";//結果64位元
			string result_put = "";
			int move = 0;//位移量
			cin >> keys >> plaintext;//讀入KEY跟原文
			keys.erase(keys.begin(), keys.begin() + 2);//消掉0x
			plaintext.erase(plaintext.begin(), plaintext.begin() + 2);//消掉0x
			for (int i = 0; i < plaintext.length(); i++)//統一轉成大寫
			{
				plaintext[i] = toupper(plaintext[i]);
			}
			for (int i = 0; i < keys.length(); i++)//轉出64位元
			{
				keys_64 += fourbits(keys[i]);
				plaintext_64 += fourbits(plaintext[i]);
			}
			//initial permutation
			string textput = "";
			for (int i = 0; i < 64; i++)
			{
				textput += plaintext_64[IP_tab[i] - 1];
				if (i > 31)//右邊
					plaintext_R += plaintext_64[IP_tab[i] - 1];
				else
					plaintext_L += plaintext_64[IP_tab[i] - 1];;
			}
			plaintext_64 = textput;//IP過後的
			//PC-1
			for (int i = 0; i < 56; i++)
			{
				keys_56 += keys_64[PC_1[i] - 1];
				if (i > 27)//右邊
					keys_R += keys_64[PC_1[i] - 1];
				else//左邊
					keys_L += keys_64[PC_1[i] - 1];
			}


			//16次Transform
			for (int i = 0; i < 16; i++)
			{
				string subset = "";
				string put = "";//暫放XOR之後的
				string r_put;//右邊原文的暫存
				string plaintext_R48 = "";//擴增後的右原文
				string keys_48 = "";//48位元key
				string keyput = "";
				string left = plaintext_R;//暫放原文
				//plaintext_L = plaintext_R;
				//決定位移量
				if (i == 0 || i == 1 || i == 8 || i == 15)
					move = 1;
				else
					move = 2;
				keys_L = LS(keys_L, move);//左Key左移
				keys_R = LS(keys_R, move);//右key左移
				keyput += keys_L;
				keyput += keys_R;
				//都弄成48bit
				for (int i = 0; i < 48; i++)
				{
					keys_48 += keyput[PC_2[i] - 1];
					plaintext_R48 += plaintext_R[E[i] - 1];
				}
				//XOR
				for (int i = 0; i < 48; i++)
				{
					put.push_back((((keys_48[i] - '0') ^ (plaintext_R48[i] - '0')) + '0'));
				}
				int count = 0;//計數要用哪個S-BOX
				for (int i = 0; i < 48; i++)
				{
					subset.push_back(put[i]);
					//6位元一組轉成對照表的
					if (subset.length() == 6 && count == 0)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S1[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 1)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S2[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 2)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S3[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 3)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S4[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 4)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S5[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 5)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S6[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 6)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S7[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 7)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S8[row * 16 + col]);
						subset.clear();
						count++;
					}
				}
				string p = "";
				//permutation
				for (int i = 0; i < 32; i++)
				{
					p += r_put[P[i] - 1];
				}
				r_put = p;
				//跟左邊原文XOR
				for (int i = 0; i < 32; i++)
				{
					plaintext_R[i] = ((r_put[i] - '0') ^ (plaintext_L[i] - '0')) + '0';
				}
				plaintext_L = left;
			}
			//串起來
			result_put += plaintext_R;
			result_put += plaintext_L;
			//IPinverse
			for (int i = 0; i < 64; i++)
			{
				result_64 += result_put[IP_inverse[i] - 1];
			}
			string sub;//4個一組轉回去
			for (int i = 0; i < 64; i++)
			{
				sub.push_back(result_64[i]);
				if (sub.length() == 4)
				{
					ciphertext.push_back(fourbit_inv(sub));
					sub.clear();
				}
			}
			cout << ciphertext;
		}
		else if (input == "./DecryptDES")
		{
			string keys;//金鑰16進制
			string keys_56;//56位元key
			string keys_L = "";
			string keys_R = "";
			string ciphertext;//密文16進制
			string ciphertext_L = "";
			string ciphertext_R = "";
			string keys_64 = "";//Key64位元
			string ciphertext_64 = "";//密文64位元
			string plaintext = "0x";//結果
			string result_64 = "";//結果64位元
			string result_put = "";
			int move = 0;//位移量
			cin >> keys >> ciphertext;//讀入KEY跟密文
			keys.erase(keys.begin(), keys.begin() + 2);//消掉0x
			ciphertext.erase(ciphertext.begin(), ciphertext.begin() + 2);//消掉0x
			for (int i = 0; i < ciphertext.length(); i++)//統一轉成大寫
			{
				ciphertext[i] = toupper(ciphertext[i]);
			}
			for (int i = 0; i < keys.length(); i++)//轉出64位元
			{
				keys_64 += fourbits(keys[i]);
				ciphertext_64 += fourbits(ciphertext[i]);
			}
			//initial permutation
			string textput = "";
			for (int i = 0; i < 64; i++)
			{
				textput += ciphertext_64[IP_tab[i] - 1];
				if (i > 31)//右邊
					ciphertext_R += ciphertext_64[IP_tab[i] - 1];
				else
					ciphertext_L += ciphertext_64[IP_tab[i] - 1];;
			}
			ciphertext_64 = textput;//IP過後的
								   //PC-1
			for (int i = 0; i < 56; i++)
			{
				keys_56 += keys_64[PC_1[i] - 1];
				if (i > 27)//右邊
					keys_R += keys_64[PC_1[i] - 1];
				else//左邊
					keys_L += keys_64[PC_1[i] - 1];
			}

			//16次Transform
			for (int i = 0; i < 16; i++)
			{
				string subset = "";
				string put = "";//暫放XOR之後的
				string r_put;//右邊密文的暫存
				string ciphertext_R48 = "";//擴增後的右密文
				string keys_48 = "";//48位元key
				string keyput = "";
				string left = ciphertext_R;//暫放原文
										  //決定位移量
				if (i == 0)
					move = 0;
				else if (i == 1 || i == 8 || i == 15)
					move = 1;
				else
					move = 2;
				keys_L = RS(keys_L, move);//左Key右移
				keys_R = RS(keys_R, move);//右key右移
				keyput += keys_L;
				keyput += keys_R;
				//都弄成48bit
				for (int i = 0; i < 48; i++)
				{
					keys_48 += keyput[PC_2[i] - 1];
					ciphertext_R48 += ciphertext_R[E[i] - 1];
				}
				//XOR
				for (int i = 0; i < 48; i++)
				{
					put.push_back((((keys_48[i] - '0') ^ (ciphertext_R48[i] - '0')) + '0'));
				}
				int count = 0;//計數要用哪個S-BOX
				for (int i = 0; i < 48; i++)
				{
					subset.push_back(put[i]);
					//6位元一組轉成對照表的
					if (subset.length() == 6 && count == 0)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S1[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 1)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S2[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 2)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S3[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 3)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S4[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 4)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S5[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 5)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S6[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 6)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S7[row * 16 + col]);
						subset.clear();
						count++;
					}
					else if (subset.length() == 6 && count == 7)
					{
						int row = ((subset[0] - '0') * 2) + subset[5] - '0';
						int col = (subset[1] - '0') * 8 + (subset[2] - '0') * 4 + (subset[3] - '0') * 2 + (subset[4] - '0');
						r_put += fourbits(S8[row * 16 + col]);
						subset.clear();
						count++;
					}
				}
				string p = "";
				//permutation
				for (int i = 0; i < 32; i++)
				{
					p += r_put[P[i] - 1];
				}
				r_put = p;
				//跟左邊密文XOR
				for (int i = 0; i < 32; i++)
				{
					ciphertext_R[i] = ((r_put[i] - '0') ^ (ciphertext_L[i] - '0')) + '0';
				}
				ciphertext_L = left;
			}
			//串起來
			result_put += ciphertext_R;
			result_put += ciphertext_L;
			//IPinverse
			for (int i = 0; i < 64; i++)
			{
				result_64 += result_put[IP_inverse[i] - 1];
			}
			string sub;//4個一組轉回去
			for (int i = 0; i < 64; i++)
			{
				sub.push_back(result_64[i]);
				if (sub.length() == 4)
				{
					plaintext.push_back(tolower(fourbit_inv(sub)));
					sub.clear();
				}
			}
			cout << plaintext;
		}
		else
			cout << "input's format is error" << endl;

	}
}
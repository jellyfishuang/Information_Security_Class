#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main()
{
	string input;//./Encrypt
	while (cin >> input)
	{
		string keys;//英文字的key
		string cipher;
		string plaintext;
		string ciphertext;
		int flag = 0;//判斷哪個cipher
		cin >> cipher;
		if (cipher == "caesar")
		{
			flag = 1;
		}
		else if (cipher == "playfair")
		{
			flag = 2;
		}
		else if (cipher == "vernam")
		{
			flag = 3;
		}
		else if (cipher == "row")
		{
			flag = 4;
		}
		else if (cipher == "rail_fence")
		{
			flag = 5;
		}
		switch (flag)
		{
		case 1: /*caesar*/
		{
			int key;//數字
			cin >> key >> plaintext;
			ciphertext = plaintext;
			for (int i = 0; i < ciphertext.length(); i++)
			{
				if (ciphertext[i] >= 'a'&&ciphertext[i] <= 'z')
				{
					ciphertext[i] = toupper(ciphertext[i]);
					ciphertext[i] += key;
					if (ciphertext[i] > 'Z')
						ciphertext[i] -= 26;
				}
			}
			cout << ciphertext;
			break;
		}
		case 2:	/*playfair*/
		{
			vector<char> AtoZ;
			vector<char> matrix_put;//一維的5x5
			vector<vector<char>> Tab;//5x5
			cin >> keys >> plaintext;
			for (int i = 0; i < plaintext.length(); i++)//將原文的j都取代成i
			{
				if (plaintext[i] == 'j')
					plaintext[i] = 'i';
			}
			for (int i = 0; i < 26; i++)//對照表
			{
				AtoZ.push_back('A' + i);
			}
			AtoZ.erase(AtoZ.begin() + 9, AtoZ.begin() + 10);
			for (int i = 0; i < keys.length(); i++)//將金鑰的J都取代成I
			{
				if (keys[i] == 'J')
					keys[i] = 'I';
			}
			for (int i = 0; i < keys.length() - 1; i++)//消掉keys裡面重複的
			{
				for (int j = i + 1; j < keys.length();)
				{
					if (keys[i] == keys[j])
						keys.erase(keys.begin() + j, keys.begin() + j + 1);
					else
					{
						j++;
					}
				}
			}
			for (int i = 0; i < keys.length(); i++)//加入金鑰
			{
				matrix_put.push_back(keys[i]);
				for (int j = 0; j < AtoZ.size(); j++)
				{
					if (keys[i] == AtoZ[j])
					{
						AtoZ.erase(AtoZ.begin() + j, AtoZ.begin() + j + 1);
					}
				}
			}
			for (int i = 0; i < AtoZ.size(); i++)//補滿剩下的字母
			{
				matrix_put.push_back(AtoZ[i]);
			}
			for (int i = 0; i < 5; i++)//轉成矩陣
			{
				vector<char> put;
				for (int j = 0; j < 5; j++)
				{
					put.push_back(matrix_put[(i * 5) + j]);
				}
				Tab.push_back(put);
			}
			for (int i = 0; i < plaintext.length(); i++)
			{
				plaintext[i] = toupper(plaintext[i]);
			}
			for (int i = 0; i < plaintext.length(); i++)
			{
				int pos_x = 0, pos_y = 0;
				if (plaintext[i] == plaintext[i + 1])//兩數字相同
				{
					plaintext.insert(plaintext.begin() + i + 1, 'X');
					i--;
				}
				else
				{
					for (int j = 0; j < 5; j++)
					{
						for (int k = 0; k < 5; k++)
						{
							if (Tab[j][k] == plaintext[i])//找出第一個字的位置
							{
								pos_x = k;
								pos_y = j;
							}
						}
					}
					i++;
					for (int j = 0; j < 5; j++)
					{
						for (int k = 0; k < 5; k++)
						{
							if (Tab[j][k] == plaintext[i])//找出第二個字的位置
							{
								if (pos_x == k)//同一column
								{
									if (pos_y == 4)
										ciphertext.push_back(Tab[0][pos_x]);//超出範圍回到0
									else
										ciphertext.push_back(Tab[pos_y + 1][pos_x]);
									if (j == 4)
										ciphertext.push_back(Tab[0][k]);//超出範圍回到0
									else
										ciphertext.push_back(Tab[j + 1][k]);

								}
								else if (pos_y == j)//同一row
								{
									if (pos_x == 4)
										ciphertext.push_back(Tab[pos_y][0]);//超出範圍回到0
									else
										ciphertext.push_back(Tab[pos_y][pos_x + 1]);
									if (k == 4)
										ciphertext.push_back(Tab[j][0]);//超出範圍回到0
									else
										ciphertext.push_back(Tab[j][k + 1]);
								}
								else
								{
									ciphertext.push_back(Tab[pos_y][k]);//自己的行，別人的列
									ciphertext.push_back(Tab[j][pos_x]);
								}
							}
						}
					}
				}
			}
			cout << ciphertext;
			break;
		}
		case 3:	/*vernam*/
		{
			cin >> keys >> plaintext;
			ciphertext = plaintext;
			for (int i = 0; i < keys.length(); i++)
			{
				ciphertext.pop_back();
			}
			ciphertext.insert(0, keys);
			for (int i = 0; i < ciphertext.length(); i++)//轉成大寫
			{
				plaintext[i] = toupper(plaintext[i]);
				ciphertext[i] = towupper(ciphertext[i]);
			}
			for (int i = 0; i < ciphertext.length(); i++)
			{
				int c_num = ciphertext[i] - 'A';//key的數字
				int p_num = plaintext[i] - 'A';//plaintext的數字
				c_num = c_num ^ p_num;
				ciphertext[i] = 'A' + c_num;
			}
			cout << ciphertext;
			break;
		}
		case 4: /*row*/
		{
			cin >> keys >> plaintext;
			vector<vector<char>> row;
			int num = ((plaintext.length() - 1) / keys.length()) + 1;//有幾行 ((n-1)/m)+1
			int count = 0;//計數原文的位置
			for (int i = 0; i < num; i++)
			{
				vector<char> put;
				for (int j = 0; j < keys.length() && count < plaintext.length(); j++, count++)
				{
					put.push_back(toupper(plaintext[count]));//轉成大寫
				}
				row.push_back(put);
			}
			for (int i = 0; i < keys.length(); i++)
			{
				char find = '1' + i;//要找的
				for (int j = 0; j < keys.length(); j++)
				{
					if (keys[j] == find)
					{
						for (int k = 0; k < num; k++)
						{
							if (j < row[k].size())//是否超過範圍
								cout << row[k][j];
						}
					}
				}
			}
			break;
		}
		case 5:	/*rail_fence*/
		{
			int key;
			cin >> key >> plaintext;
			vector<vector<char>>  rail;//籬笆
			int flag = 0;//判斷往上往下
			for (int i = 0; i < key; i++)//建立一個空的籬笆 plaintext長Xkey
			{
				vector<char> put;//暫放
				for (int j = 0; j < plaintext.length(); j++)
				{
					put.push_back(' ');
				}
				rail.push_back(put);
			}
			for (int i = 0, count = 0; count < 1; count++)
			{
				for (int j = 0; j < plaintext.length(); j++)
				{
					if (i == 0)
					{
						rail[i][j] = plaintext[j];
						flag = 0;
						i++;
					}
					else if (i == key - 1)
					{
						rail[i][j] = plaintext[j];
						flag = 1;//往上
						i--;
					}
					else
					{
						if (flag == 0)
						{
							rail[i][j] = plaintext[j];
							i++;
						}
						else if (flag == 1)
						{
							rail[i][j] = plaintext[j];
							i--;
						}
					}
				}
			}
			for (int i = 0; i < key; i++)//尋找非初始化的字加入結果
			{
				for (int j = 0; j < plaintext.length(); j++)
				{
					if (rail[i][j] != ' ')
					{
						ciphertext += toupper(rail[i][j]);
					}
				}
			}
			cout << ciphertext;
			break;
		}
		/*error*/
		default:
			cout << "Error input." << endl;
			break;
		}
	}
	return 0;
}
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
		string keys;//�^��r��key
		string cipher;
		string plaintext;
		string ciphertext;
		int flag = 0;//�P�_����cipher
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
			int key;//�Ʀr
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
			vector<char> matrix_put;//�@����5x5
			vector<vector<char>> Tab;//5x5
			cin >> keys >> plaintext;
			for (int i = 0; i < plaintext.length(); i++)//�N��媺j�����N��i
			{
				if (plaintext[i] == 'j')
					plaintext[i] = 'i';
			}
			for (int i = 0; i < 26; i++)//��Ӫ�
			{
				AtoZ.push_back('A' + i);
			}
			AtoZ.erase(AtoZ.begin() + 9, AtoZ.begin() + 10);
			for (int i = 0; i < keys.length(); i++)//�N���_��J�����N��I
			{
				if (keys[i] == 'J')
					keys[i] = 'I';
			}
			for (int i = 0; i < keys.length() - 1; i++)//����keys�̭����ƪ�
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
			for (int i = 0; i < keys.length(); i++)//�[�J���_
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
			for (int i = 0; i < AtoZ.size(); i++)//�ɺ��ѤU���r��
			{
				matrix_put.push_back(AtoZ[i]);
			}
			for (int i = 0; i < 5; i++)//�ন�x�}
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
				if (plaintext[i] == plaintext[i + 1])//��Ʀr�ۦP
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
							if (Tab[j][k] == plaintext[i])//��X�Ĥ@�Ӧr����m
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
							if (Tab[j][k] == plaintext[i])//��X�ĤG�Ӧr����m
							{
								if (pos_x == k)//�P�@column
								{
									if (pos_y == 4)
										ciphertext.push_back(Tab[0][pos_x]);//�W�X�d��^��0
									else
										ciphertext.push_back(Tab[pos_y + 1][pos_x]);
									if (j == 4)
										ciphertext.push_back(Tab[0][k]);//�W�X�d��^��0
									else
										ciphertext.push_back(Tab[j + 1][k]);

								}
								else if (pos_y == j)//�P�@row
								{
									if (pos_x == 4)
										ciphertext.push_back(Tab[pos_y][0]);//�W�X�d��^��0
									else
										ciphertext.push_back(Tab[pos_y][pos_x + 1]);
									if (k == 4)
										ciphertext.push_back(Tab[j][0]);//�W�X�d��^��0
									else
										ciphertext.push_back(Tab[j][k + 1]);
								}
								else
								{
									ciphertext.push_back(Tab[pos_y][k]);//�ۤv����A�O�H���C
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
			for (int i = 0; i < ciphertext.length(); i++)//�ন�j�g
			{
				plaintext[i] = toupper(plaintext[i]);
				ciphertext[i] = towupper(ciphertext[i]);
			}
			for (int i = 0; i < ciphertext.length(); i++)
			{
				int c_num = ciphertext[i] - 'A';//key���Ʀr
				int p_num = plaintext[i] - 'A';//plaintext���Ʀr
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
			int num = ((plaintext.length() - 1) / keys.length()) + 1;//���X�� ((n-1)/m)+1
			int count = 0;//�p�ƭ�媺��m
			for (int i = 0; i < num; i++)
			{
				vector<char> put;
				for (int j = 0; j < keys.length() && count < plaintext.length(); j++, count++)
				{
					put.push_back(toupper(plaintext[count]));//�ন�j�g
				}
				row.push_back(put);
			}
			for (int i = 0; i < keys.length(); i++)
			{
				char find = '1' + i;//�n�䪺
				for (int j = 0; j < keys.length(); j++)
				{
					if (keys[j] == find)
					{
						for (int k = 0; k < num; k++)
						{
							if (j < row[k].size())//�O�_�W�L�d��
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
			vector<vector<char>>  rail;//�X��
			int flag = 0;//�P�_���W���U
			for (int i = 0; i < key; i++)//�إߤ@�ӪŪ��X�� plaintext��Xkey
			{
				vector<char> put;//�ȩ�
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
						flag = 1;//���W
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
			for (int i = 0; i < key; i++)//�M��D��l�ƪ��r�[�J���G
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
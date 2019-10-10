#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	//./Decrypt
	string input;
	while (cin >> input)
	{
		string keys;
		string cipher;
		string plaintext;
		//keepgoingnevergiveup
		string ciphertext;
		int flag = 0;

		//�P�_����cipher
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
		//caesar
		case 1:
		{
			int key;
			cin >> key >> ciphertext;
			plaintext = ciphertext;
			for (int i = 0; i < plaintext.length(); i++)
			{
				if (plaintext[i] >= 'A'&& plaintext[i] <= 'Z')
				{
					plaintext[i] = tolower(plaintext[i]);
					plaintext[i] -= key;
					if (plaintext[i] < 'a')
						plaintext[i] += 26;
				}
			}
			cout << plaintext;
			break;
		}
		//playfair
		case 2:
		{
			string key;
			cin >> key >> ciphertext;
			plaintext = ciphertext;

			char word = 'a';
			bool check = false;
			char table[5][5];

			for (int i = 0; i < key.size(); i++)
			{
				key[i] = tolower(key[i]);
			}
			//�ɻ�table
			for (;;)
			{
				for (int i = 0; i < key.size(); i++)
				{
					if (key[i] == word)
					{
						check = true;
						break;
					}
				}
				if (check)
				{
					check = false;
					word += 1;
					//�ѤU���Ŷ��N���[�J���^��r����a-z�����ǥ[�J�]�NI�MJ���@�P�@�r�C�^
					if (word == 'i')
						word += 1;
				}
				else
					key += word;

				if (key.size() == 25)
					break;
			}
			//�ন�G���x�}
			int key_index = 0;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
					table[i][j] = key[key_index++];
			}
			cout << table[0][0];


			break;
		}
		//vernam
		case 3:	
		{
			string key;
			cin >> key >> ciphertext;
			plaintext = ciphertext;
			int count = ciphertext.size() / key.size();
			int keysize = key.size();
			int ciphersize = ciphertext.size();

			//����_���פp��K��A��XOR����X�Ӫ�����Y�O����K�媺���_�A�A��XOR
			string changekey = key;
			string answer;

			for (int i = 0; i < ciphersize;i++)
			{
				int j = 0;
				for (; j < keysize;)
				{
					int c_num = changekey[j] - 'A';
					int p_num = ciphertext[i+j] - 'A';
					changekey[j] = (c_num xor p_num) + 'A';
					answer.push_back((c_num xor p_num )+ 'A');
					if (j < (keysize - 1))
						j++;
					else
						break;
				}
				//���_���פp�󵥩�
				if ((i + j + 1) <= ciphersize)
				{
					i = i + j;
				}
				//���_���פj��
				else
				{
					int remind = ciphersize - (i + j + 1);
					for (int k = 0; k < remind; k++)
					{
						int c_num = changekey[j] - 'A';
						int p_num = ciphertext[i + j] - 'A';
						answer.push_back((c_num xor p_num) + 'A');
					}
					break;
				}
			}
			//��p�g
			for (int i = 0; i < answer.size(); i++)
			{
				answer[i] = tolower(answer[i]);
			}
			cout << answer;

			/*
			for (int i = 0; i < keysize; i++)
			{
				plaintext.pop_back();
			}
			plaintext.insert(0, key);
			for (int i = 0; i < ciphersize; i++)//�ন�p�g
			{
				plaintext[i] = tolower(plaintext[i]);
				ciphertext[i] = tolower(ciphertext[i]);
			}

			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < keysize; j++)
				{
					plaintext[i*keysize+j] += (((ciphertext[i*keysize + j] - 'a') xor (key[j] - 'a')) + 'a');
					//���s���N��key
					key[j] = plaintext[i*keysize + j];
				}
			}
			int reminder = ciphersize - (count*keysize);
			for (int i = 0; i < reminder; i++)
			{
				plaintext.push_back(((ciphertext[count*keysize + i] - 'a') xor (key[i] - 'a')) + 'a');
			}
			*/
			/*
			string tmpKey;
			int intKey = key.length();
			//�]�w����
			for (int i = 0; i < ciphertext.length(); i++)
			{
				plaintext[i] = ' ';
			}
			int flag = 0;
			for(;;)
			{
				plaintext.insert(flag, key);
				//�p�G���_���פp��K��
				if ((flag + intKey) < plaintext.length())
					flag = flag + intKey;
				//�p�G�[�W�h�|�j��ε��� �h�񺡳ѤU���Ů����X
				else
				{
					int reminder = flag + intKey - plaintext.length();

					break;
				}
			}
			*/
			/*
			for (int i = 0; i < key.length(); i++)
			{
				plaintext.pop_back();
			}
			plaintext.insert(0, key);
			//��p�g
			for (int i = 0; i < ciphertext.length(); i++)
			{
				plaintext[i] = tolower(plaintext[i]);
				ciphertext[i] = tolower(ciphertext[i]);
			}
			
			string changekey;
			for (int i = 0; i < ciphertext.length(); i++)
			{
				if (i*(key.length() + 1) <= ciphertext.length())
				{
					for (int j = 0; j < key.length(); j++)
					{
						changekey[j] = ciphertext[i*key.length() + j];
					}
					int c_num = changekey[i] - 'a';
					int p_num = plaintext[i] - 'a';
					p_num = p_num ^ c_num;
					plaintext[i] = p_num + 'a';
				}
				else
				{

				}
				
			}
			*/
			//cout << plaintext;
			break;
		}
		//row
		case 4:
		{
			string key;
			cin >> key >> ciphertext;

			vector<vector<char>> row;
			//���X��
			int ciphersize = ciphertext.size();
			int keysize = key.size();
			int quotient = ciphersize / keysize;
			int reminder = ciphersize % keysize;

			queue<char> col;
			for (int i = 0; i < ciphersize; i++)
			{
				col.push(ciphertext[i]);
			}
			//���Ψæs�Jrow
			for (int i = 0; i < keysize; i++)
			{
				vector<char> put;
				if (reminder >= 1)
				{
					for (int j = 0; j < quotient; j++)
					{
						char tmp = col.front();
						col.pop();
						put.push_back(tmp);
					}
					char tmp = col.front();
					col.pop();
					put.push_back(tmp);
					reminder--;
				}
				else
				{
					for (int j = 0; j < quotient; j++)
					{
						char tmp = col.front();
						col.pop();
						put.push_back(tmp);
					}
				}
				row.push_back(put);
			}
			//�洫����
			vector<vector<char>> answer;
			for (int i = 0; i < keysize; i++)
			{
				for (int j = 0; j < keysize; j++)
				{
					char find = '1' + j;
					if (find == key[i])
					{
						vector<char> put;
						for (int k = 0; k < row[j].size(); k++)
						{
							put.push_back(row[j][k]);
						}
						answer.push_back(put);
					}
				}
			}
			//�ѥX����
			int remi = ciphersize % keysize;
			for (int i = 0; i < quotient; i++)
			{

				for (int k = 0; k < keysize; k++)
				{
					if(answer[k][i]!= NULL)
						plaintext.push_back(answer[k][i]);
				}
			}
			//�B�z�h�l���Ů� �⤣���@�ƾ�C����W�ԥX��J����
			int flag = 0;
			while(remi >= 1)
			{
				plaintext.push_back(answer[flag][quotient]);
				remi--;
				flag++;
			}
			//�ন�p�g
			for (int i = 0; i < plaintext.size(); i++)
			{
				plaintext[i] = tolower(plaintext[i]);
			}
			cout << plaintext;
			break;
			/*
			int col = ((ciphertext.length() - 1) / key.length()) + 1;
			int count = 0;
			int row = ciphertext.size();
			//��J�x�}
			for (int i = 0; i < key.length(); i++)
			{
				vector<char> put;
				for (int j = 0; j < col; j++)
				{
					//put.push_back(ciphertext);
				}
			}
			for (int i = 0; i < col; i++)
			{
				vector<char> put;
				for (int j = 0; j < key.length() && count < ciphertext.length(); j++, count++)
				{
					put.push_back(tolower(ciphertext[count]));
				}
				row.push_back(put);
			}
			*/
		}
		//rail_fence
		case 5:
		{
			//key�N���X�C�X��
			int key;
			cin >> key >> ciphertext;
			vector<vector<char>> Rail;

			//�إX��n�d���X��
			for (int i = 0; i < key; i++)
			{
				vector<char> put;
				//���ઽ���s�J �޼ƽĬ�
				for (int j = 0; j < ciphertext.length(); j++)
				{
					put.push_back(' ');
				}
				Rail.push_back(put);
			}
			//��V
			bool direction;
			int row = 0, col = 0;
			//�аO�óB�z��V
			for (int i = 0; i < ciphertext.length(); i++)
			{
				//�ˬd��Ĥ@���X��
				if (row == 0)
					direction = true;
				//�ˬd��̫�@���X��
				if (row == key - 1)
					direction = false;

				//�аO
				Rail[row][col++] = '*';

				if (direction == true)
					row++;
				else
					row--;
			}
			//�K���J�i�X��
			int index = 0;
			for (int i = 0; i < key; i++)
			{
				for (int j = 0; j < ciphertext.length(); j++)
				{
					if (Rail[i][j] == '*' && index < ciphertext.length())
					{
						Rail[i][j] = ciphertext[index++];
					}
				}
			}
			//���X���ন����
			row = 0; col = 0;
			for (int i = 0; i < ciphertext.length(); i++)
			{
				//�ˬd��Ĥ@���X��
				if (row == 0)
					direction = true;
				//�ˬd��̫�@���X��
				if (row == key - 1)
					direction = false;

				if (Rail[row][col] != '*')
					plaintext.push_back(Rail[row][col++]);

				if (direction == true)
					row++;
				else
					row--;
			}
			for (int i = 0; i < plaintext.length(); i++)
			{
				plaintext[i] = tolower(plaintext[i]);
			}
			cout << plaintext;
			break;
			/*
			int Plen = key * 2 - 2;
			//Plen = �@�骺����
			int quotient = ciphertext.length / Plen;
			//��
			int remainder = ciphertext.length / Plen;
			//�l�� = �����@���Ѿl���Z��
			int offset = 0;

			for (int i = 0; i < key; i++)
			{
				int j = i + 1;
				//�X�����Ƽ�
				bool isFirstOrLast = (j == 1 || j == key);
				//�O���O�Ĥ@�Ʃγ̫�@���X��
				int Length = isFirstOrLast ? quotient : quotient * 2;
				//�Ĥ@�ƻP�̫�@���X���u�|�Q���@��

				if (j <= remainder)
				{
					Length++;
					//�h�{
					if (!isFirstOrLast)
					//�^�{
					{
						if (((key - j) * 2 + j) <= remainder)
						{
							Length++;
						}
					}
				}
				for (int k = 0; k < Length; k++)
				{
					Rail[i].push_back(ciphertext.substr(offset, 1));
				}
			}*/
		}
		default:
			cout << "Error input." << endl;
			break;
		}
	}
	return 0;
}
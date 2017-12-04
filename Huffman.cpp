#include<iostream>
using namespace std;
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<cstring>
#include<cctype>


///////////////////////////////����� 
class Node
{
private:
	int frequence; //Ƶ�� 
	char value;    //ֵ 
	Node* parent;  //ָ�򸸽���ָ�� 
	Node* left;    //ָ�����ӽڵ��ָ�� 
	Node* right;   //ָ�����ӽڵ��ָ�� 
public:
	Node();     
	Node(int fq);
	void setValue(char ch); //���ý��ֵ 
	void setF(int fq);  //���ý��Ƶ�� 
	void setCode(char pathcode[]);  //����ֵ����Ӧ�ı��� 
	void incrOne();  //�ڴ���ֵ��Ƶ��ʱ���ڼ�1�ĺ��� 
	int getF();  //��ȡֵ����ӦƵ�� 
	char getValue(); //��ȡֵ 
	void setLeft(Node* left);  //�������ӽڵ� 
	void setRight(Node* right);  //�������ӽڵ� 
	void setParent(Node* parent);  //���ø��ڵ� 
	Node* getLeft(); //��ȡ���ӽڵ� 
	Node* getRight(); //��ȡ���ӽڵ� 
	Node* getParent(); //��ȡ���ڵ� 

};



Node::Node()
{
	frequence = 0;
	parent = left = right = NULL;
}


Node::Node(int fq)
{
	frequence = fq;
	parent = left = right = NULL;
}



void Node::setValue(char ch)
{
	value = ch;
}

void Node::setF(int fq)
{
	frequence = fq;
}




void Node::incrOne()
{
	frequence++;
}

int Node::getF()
{
	return frequence;
}

char Node::getValue()
{
	return value;
}



void Node::setLeft(Node* left)
{
	this->left = left;
}

void Node::setRight(Node* right)
{
	this->right = right;
}


void Node::setParent(Node* parent)
{
	this->parent = parent;
}


Node* Node::getLeft()
{
	return left;
}

Node* Node::getRight()
{
	return right;
}


Node* Node::getParent()
{
	return parent;
}


//////////////////////////////////Huffman���� 
template<class Node>
class Huffman
{
private:
	Node* root;//���ڵ� 
	int sum;  //������� 
public:
	char code[26][100]; //26����ĸ�ֱ��Ӧ�ı��� 
	Huffman();
	void createHuffman(Node* num, int n);//�������鴴��Huffman�� 
	void selectNode(Node* node, int& r1, int& r2,int currsize);//�Խ������������򣬰�Ƶ�ʴӵ͵��� 
	void findLeaf_Code(Node* temp, char pathcode[], int k);  //��Ҷ�ڵ���б��� 
	bool isLeaf(Node* node);//�ж��Ƿ�ΪҶ�ڵ� 
	Node* getRoot(); //���ظ��ڵ� 
};


template<class Node>
Huffman<Node>::Huffman()
{
	root = NULL;
	sum = 0;
	for(int i=0;i<26;i++)
	{
		memset(code[i],0,sizeof(char)*100);
	}
	
}


template<class Node>
void Huffman<Node>::createHuffman(Node* num, int n)
{
	int k = 0;
	sum = 2 * n - 1;
	while (n + k < sum)
	{
		int r1=0, r2=0;
		selectNode(num, r1, r2,n+k);
		int temp = num[r1].getF() + num[r2].getF();
		num[n + k].setF(temp);
		num[n + k].setLeft(&num[r1]);
		num[n + k].setRight(&num[r2]);
		num[r1].setParent(&num[n + k]);
		num[r2].setParent(&num[n + k]);
		k++;
	}
	root = &num[sum-1];
}



template<class Node>
void Huffman<Node>::selectNode(Node* node, int& r1, int& r2,int currsize)
{
	int k=0;
	while(node[k].getParent()!=NULL)
	{
		k++;
	}
	r1 = r2 = k;
	for (int i = r1; i<currsize-1; i++)
	{
		if (node[i+1].getParent()==NULL&&node[r1].getF()>node[i + 1].getF())
		{
			r1 = i + 1;
		}
	}
	if(r1==r2)
	{
		while(node[++r2].getParent()!=NULL);
	}
	for (int i = r2; i<currsize-1; i++)
	{
		if ((i + 1) != r1&&node[i+1].getParent()==NULL&&node[r2].getF()>node[i + 1].getF())
		{
			r2 = i + 1;
		}
	}
}



template<class Node>
void Huffman<Node>::findLeaf_Code(Node* temp, char pathcode[], int k)////��ʼʱ k=-1 
{
	if (k != -1)
	{
		if (isLeaf(temp))
		{
			if (temp->getParent()->getLeft() == temp)
			{
				pathcode[k] = '0';
			}
			else if (temp->getParent()->getRight() == temp)
			{
				pathcode[k] = '1';
			}
			
			for(int i=0;i<k+1;i++)
			{
				code[(int)temp->getValue() - 97][i]=pathcode[i];
			}//(int)temp->getValue()-97:for example, value is a,the result is 0
			
			return;
		}
		else if (temp->getParent()->getLeft() == temp)
		{
			pathcode[k] = '0';
		}
		else
		{
			pathcode[k] = '1';
		}
	}
	findLeaf_Code(temp->getLeft(), pathcode, k + 1);
	findLeaf_Code(temp->getRight(), pathcode, k + 1);
}





template<class Node>
bool Huffman<Node>::isLeaf(Node* node)
{
	if (node->getLeft() == NULL&&node->getRight() == NULL)
	{
		return true;
	}
	return false;
}


template<class Node>
Node* Huffman<Node>::getRoot()
{
	return root;
}







///////////////////////////////////////////////������ 
template<class Node>
class Operation
{
private:
	Node character[26];//�����ļ��е���ĸƵ�� 
	Node temp[26];//����ȥ��Ƶ��Ϊ0����ĸ�����ĸƵ�ʼ�ֵ 
	int size;//��¼Ƶ�ʲ�Ϊ0����ĸ������ 
	Huffman<Node> tree;
public:
	Operation();
	void countFrequence(char filename[]);//�����ļ��и��ַ�����Ƶ�� 
	void cutZero();//�����������Ƶ��Ϊ0��Ԫ�ؼ�ȥ������ʣ��Ԫ�ط���temp������ 
	void BuildHuffman(); //����temp���鼰sizeֵ����Huffman�� 
	void Compress(char sourcefilename[], char aimfilename[]);//���� 
	void Decompress(char sourcefilename[],char aimfilename[]);//���� 
};


template<class Node>
Operation<Node>::Operation()
{
	size = 0;
}


/////////////////////xd///////////////////�����ļ��и��ַ�����Ƶ�� 
template<class Node>
void Operation<Node>::countFrequence(char filename[])
{
	fstream file;
	file.open(filename, ios::in);
	char ch = '?';
	file >> ch;
	while (!file.eof())
	{
		switch (ch)
		{
		case 'a':
		{
					character[0].incrOne();
					break;
		}
		case 'b':
		{
					character[1].incrOne();
					break;
		}
		case 'c':
		{
					character[2].incrOne();
					break;
		}
		case 'd':
		{
					character[3].incrOne();
					break;
		}
		case 'e':
		{
					character[4].incrOne();
					break;
		}
		case 'f':
		{
					character[5].incrOne();
					break;
		}
		case 'g':
		{
					character[6].incrOne();
					break;
		}
		case 'h':
		{
					character[7].incrOne();
					break;
		}
		case 'i':
		{
					character[8].incrOne();
					break;
		}
		case 'j':
		{
					character[9].incrOne();
					break;
		}

		case 'k':
		{
					character[10].incrOne();
					break;
		}
		case  'l':
		{
					 character[11].incrOne();
					 break;
		}
		case 'm':
		{
					character[12].incrOne();
					break;
		}
		case 'n':
		{
					character[13].incrOne();
					break;
		}
		case 'o':
		{
					character[14].incrOne();
					break;
		}
		case 'p':
		{
					character[15].incrOne();
					break;
		}
		case 'q':
		{
					character[16].incrOne();
					break;
		}
		case 'r':
		{
					character[17].incrOne();
					break;
		}
		case 's':
		{
					character[18].incrOne();
					break;
		}
		case 't':
		{
					character[19].incrOne();
					break;
		}
		case 'u':
		{
					character[20].incrOne();
					break;
		}
		case 'v':
		{
					character[21].incrOne();
					break;
		}
		case 'w':
		{
					character[22].incrOne();
					break;
		}

		case 'x':
		{
					character[23].incrOne();
					break;
		}
		case 'y':
		{
					character[24].incrOne();
					break;
		}
		case 'z':
		{
					character[25].incrOne();
					break;
		}
		default:
		{
				   cout << endl << endl << "Sorry! some content in the file is not supported in this version" << endl;
				   cout << "The program will exit 3 seconds later" << endl;
				   Sleep(3000);
				   exit(-1);
		}
		}
		file >> ch;
	}
	file.close();
}




//////////////////////////////�����������Ƶ��Ϊ0��Ԫ�ؼ�ȥ������ʣ��Ԫ�ط���temp������ 
template<class Node>
void Operation<Node>::cutZero()
{
	for (int i = 0, k = 0; i<26; i++)
	{
		if (character[i].getF() != 0)
		{
			temp[k].setValue(97 + i);
			temp[k++].setF(character[i].getF());
			size++;
		}
	}

}

/////////////////////////////////////����temp���鼰size��ֵ����Huffman�� 
template<class Node>
void Operation<Node>::BuildHuffman()
{
	tree.createHuffman(temp, size);

}



//////////////////////////////////���� 
template<class Node>
void Operation<Node>::Compress(char sourcefilename[], char aimfilename[])
{
	char pathcode[100];
	countFrequence(sourcefilename);
	cutZero();
	BuildHuffman();
	tree.findLeaf_Code(tree.getRoot(), pathcode, -1);
	fstream sourceFile;
	fstream compressFile;
	sourceFile.open(sourcefilename, ios::in);
	compressFile.open(aimfilename, ios::out);
	char ch;
	sourceFile >> ch;
	while (!sourceFile.eof())
	{
		compressFile << tree.code[(int)ch - 97];
		sourceFile >> ch;
	}
	sourceFile.close();
	compressFile.close();
}



////////////////////////////////����
template<class Node>
void Operation<Node>::Decompress(char sourcefilename[],char aimfilename[])
{
	fstream sfile;
	fstream afile;
	Node* temp=tree.getRoot();
	sfile.open(sourcefilename,ios::in);
	afile.open(aimfilename,ios::out);
	char ch='0';
	sfile>>ch;
	while(!sfile.eof())
	{
		while(!tree.isLeaf(temp))
		{
			if(ch=='0')
			{
				temp=temp->getLeft();
			}
			else
			{
				temp=temp->getRight();
			}
			sfile>>ch;
		}
		char letter=temp->getValue();
		afile<<letter;
		temp=tree.getRoot();
	}
	sfile.close();
	afile.close();
}






int main(void)
{
	Operation<Node> operate;
	while (1)
	{
		cout << "*" << "1. Compress" << endl;
		cout << "*" << "2. Decompresss" << endl;
		cout << "*" << "3. Exit" << endl << endl;
		cout << "Please choose the selection you need:";
		int flag;
		cin >> flag;
		switch (flag)
		{
			case 1:
			{
				cout << endl << "Please input source file name<size less than 4GB>:";
				char sourcefilename[100];
				char aimfilename[100];
				cin >> sourcefilename;
				cout << endl << "Please aim source file name to store the compressed result:";
				cin >> aimfilename;
				operate.Compress(sourcefilename, aimfilename);
				break;
			}
			case 2:
			{
					cout<<endl<<"Please input source file name<size less than 4GB>:";
					char sourcefilename[100];
					char aimfilename[100];
					cin >> sourcefilename;
					cout << endl << "Please aim source file name to store the decompressed result:";
					cin >> aimfilename;
					operate.Decompress(sourcefilename,aimfilename);
					break;
			}
			case 3:
			{
					  exit(-1);
			}
			default:
			{
				cout << "Select number is not 1 or 2 or 3, please check it and select again" << endl;
				cout << "Please choose the selection you need:";
			}
		}
		cout<<endl<<endl<<"Continue? Y/N:";
		char yorn;
		int hot=1;
		while(hot)
		{
			cin>>yorn;
			yorn=toupper(yorn);
			switch(yorn)
			{
				case'Y':
					{
						system("cls");
						hot=0;
						break;
					}
				case'N':
					{
						exit(-1);
					}
				default:
					{
						cout<<"Sorry, your input character is not correct,please re-input:";
					}
			}
		}
	}

	return 0;
}











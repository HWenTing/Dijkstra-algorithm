#include<iostream>
#include<string>
using namespace std;

//��¼��㵽ÿ����������·������Ϣ
struct Dis {
	string path;
	int value;
	bool visit;
	Dis() {
		visit = false; //��Ӧ�Ѿ��ҵ������·���ļ���
		value = 0; //����·������
		path = ""; //��¼·����Ϣ
	}
};

//�ڽ�����Node�ڵ�
struct Node {
	int element;
	int value;
	Node *next;
	Node() {}
	Node(int element, int value) {
		this->element = element;
		this->value = value;
	}
};

/*

ͼ�Ĵ洢�ṹΪ�ڽ�����ʱ����Ӧ��Graph_AL��

*/

class Graph_AL {
private:
	int vexnum;//ͼ�Ķ������
	int edge;//ͼ�ı���
	Node *aList;//�ڽ�����
	Dis *dis;//��¼�����������·������Ϣ
public:
	//���캯��
	Graph_AL(int vexnum, int edge);
	//��������
	~Graph_AL();
	// �ߵĺϷ��Լ�� ; �����1��ʼ���
	bool check_edge_value(int start, int end, int weight);
	//����ͼ
	void createGraph();
	//��ӡ�ڽ�����
	void print();
	//�����·��
	void Dijkstra(int begin);
	//��ӡ���·��
	void print_path(int);
};

//���캯��
Graph_AL::Graph_AL(int vexnum, int edge) {
	//��ʼ������ͱ�
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӱ��ٿռ�
	aList = new Node[this->vexnum];
	dis = new Dis[this->vexnum];
	//��ʼ��
	for (int i = 0;i < this->vexnum;i++) {
		aList[i].element = i;
		aList[i].next = NULL;
	}

}

//��������
Graph_AL::~Graph_AL() {
	//�ͷſռ�
	delete[] dis;
	delete[] aList;
}

// �ߵĺϷ��Լ�� ; �����1��ʼ���
bool Graph_AL::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

//����ͼ
void Graph_AL::createGraph() {
	cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//�����жϱߵ���Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		//���ڽ����������
		Node *current2 = aList[start - 1].next;

		aList[start - 1].next = new Node(end, weight);
		aList[start - 1].next->next = current2;
		count++;

	}
}

//��ӡ�ڽ�����
void Graph_AL::print() {
	cout << "ͼ���ڽ�����Ϊ��" << endl;
	for (int i = 0;i < this->vexnum;i++) {
		Node *current1 = aList[i].next;
		cout << i + 1;
		while (current1 != NULL) {
			cout << "--->" << current1->element;
			current1 = current1->next;
		}
		cout << endl;
	}
}

//�����·��
void Graph_AL::Dijkstra(int begin) {
	Node current = aList[begin - 1];

	//��ʼ��Dis
	for (int i = 0;i < this->vexnum;i++) {
		dis[i].value = INT_MAX;
	}
	dis[begin - 1].path = "v" + to_string(begin) + "-->v" + to_string(begin);

	while (current.next != NULL) {
		//���õ�ǰ��·��
		current = *current.next;
		dis[current.element - 1].path = "v" + to_string(begin) + "-->v" + to_string(current.element);
		dis[current.element - 1].value = current.value;
	}

	//�������ĵ�����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (int i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;

		for (int i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit) {
				Node icurrent = aList[temp];
				while (icurrent.next != NULL) {
					icurrent = *icurrent.next;
					if (icurrent.element == i + 1 && (dis[temp].value + icurrent.value) < dis[i].value) {
						//����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
						dis[i].value = dis[temp].value + icurrent.value;
						dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
					}
				}
			}
		}
	}
}

//��ӡ���·��
void Graph_AL::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ��" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << "v" + to_string(begin) + "-->v" + to_string(i + 1) << "�������·����" << endl;
		}
	}
}




/*

ͼ�Ĵ洢�ṹΪ�ڽӾ���ʱ����Ӧ��Graph_DG��

*/



class Graph_DG {
private:
	int vexnum;   //ͼ�Ķ������
	int edge;     //ͼ�ı���
	int **arc;   //�ڽӾ���
	Dis * dis;   //��¼�����������·������Ϣ

public:
	//���캯��
	Graph_DG(int vexnum, int edge);
	//��������
	~Graph_DG();
	// �ߵĺϷ��Լ�� ; �����1��ʼ���
	bool check_edge_value(int start, int end, int weight);
	//����ͼ
	void createGraph();
	//��ӡ�ڽӾ���
	void print();
	//�����·��
	void Dijkstra(int begin);
	//��ӡ���·��
	void print_path(int);
};

//���캯��
Graph_DG::Graph_DG(int vexnum, int edge) {
	//��ʼ���������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
	arc = new int*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//�ڽӾ����ʼ��Ϊ�����
			arc[i][k] = INT_MAX;
		}
	}
}

//��������
Graph_DG::~Graph_DG() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
}

// �ߵĺϷ��Լ��; �����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

//����ͼ
void Graph_DG::createGraph() {
	cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//�����жϱߵ���Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		//���ڽӾ����Ӧ�ϵĵ㸳ֵ
		arc[start - 1][end - 1] = weight;
		//�Ա߼���
		++count;
	}
}

//��ӡ�ڽӾ���
void Graph_DG::print() {
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0; //��ӡ�еı�ǩ
	int count_col = 0; //��ӡ�еı�ǩ
					   //��ʼ��ӡ
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)//�����ڱ�
				cout << "��" << " ";
			else //���ڶ�Ӧ�ı�
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

//�����·��
void Graph_DG::Dijkstra(int begin) {
	//��ʼ��dis����
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//���õ�ǰ��·��
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	//�������ĵ�����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//����Դ�㵽������ľ�����Ϣ
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
			}
		}
	}
}

//��ӡ���·��
void Graph_DG::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ��" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX && dis[i].value >= 0)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << "v" + to_string(begin) + "-->v" + to_string(i + 1) << "�������·����" << endl;
		}
	}
}



/*

ͼ�Ĵ洢�ṹΪ�߼�����ʱ����Ӧ��Graph_EA��

*/


struct Edge {
	int begin;//��¼���
	int end;//��¼β��
	int weight;//��¼Ȩ��
	Edge() {
		begin = 0;
		end = 0;
		weight = 0;
	}
};
/*
�洢�ṹΪ�߼�����
*/

class Graph_EA {
private:
	int vexnum;   //ͼ�Ķ������
	int edge;     //ͼ�ı���
	Edge * edges;   //�ڽӾ���
	Dis * dis;   //��¼�����������·������Ϣ
public:
	//���캯��
	Graph_EA(int vexnum, int edge);
	//��������
	~Graph_EA();
	// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
	//�����1��ʼ���
	bool check_edge_value(int start, int end, int weight);
	//����ͼ
	void createGraph();
	//��ӡ�ڽӾ���
	void print();
	//�����·��
	void Dijkstra(int begin);
	//��ӡ���·��
	void print_path(int);
};


//���캯��
Graph_EA::Graph_EA(int vexnum, int edge) {
	//��ʼ���������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
	edges = new Edge[this->edge];
	dis = new Dis[this->vexnum];
	
}

//��������
Graph_EA::~Graph_EA() {
	delete[] dis;
	
	delete []edges;
}



// �ߵĺϷ��Լ��; �����1��ʼ���
bool Graph_EA::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}


//����ͼ
void Graph_EA::createGraph() {
	cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;//���
	int end;//β��
	int weight;//Ȩ��
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//�����жϱߵ���Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		edges[count].begin = start;
		edges[count].end = end;
		edges[count].weight = weight;
		++count;
	}
}


//��ӡ�߼�����
void Graph_EA::print() {
	cout << "ͼ�ı߼�����Ϊ��" << endl;
	cout << "������	      begin     end    weight" << endl;
	for (int i = 0;i < this->edge;i++) {
		cout << "edges[" + to_string(i) + "]	" << to_string(edges[i].begin) + "	" 
			<< to_string(edges[i].end) + "	" << to_string(edges[i].weight) << endl;
	}

}


//�����·��
void Graph_EA::Dijkstra(int begin) {
	//���ȳ�ʼ�����ǵ�dis����
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//���õ�ǰ��·��
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = INT_MAX;
	}
	for (i = 0;i < this->edge;i++) {
		if (edges[i].begin == begin) {
			dis[edges[i].end-1].value = edges[i].weight;
		}
	}


	//�������ĵ�����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩

	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;
		for (int j = 0;j < this->edge;j++) {
			if (edges[j].begin-1 == temp) {//�ж��Ƿ�Ҫ����
				if (!dis[edges[j].end-1].visit && (dis[temp].value + edges[j].weight) < dis[edges[j].end-1].value) {
					//����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
					dis[edges[j].end-1].value = dis[temp].value + edges[j].weight;
					dis[edges[j].end-1].path = dis[temp].path + "-->v" + to_string(edges[j].end);
				}
			}
		}
	}
	
}


//��ӡ���·��
void Graph_EA::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ��" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX && dis[i].value >= 0)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << "v" + to_string(begin) + "-->v" + to_string(i + 1) << "�������·����" << endl;
		}
	}
}



//������붥��ͱߵ���Ϣ
bool check(int Vexnum, int edge) {
	if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
		return false;
	return true;
}



//main����
int main() {
	int vexnum; 
	int edge;
	int choice; 
	int source;
	char q;
	cout << "Dijkstra�㷨������Դ�㵽��������������·��" << endl;
	//��������û�����
	do {
		//��ȡͼ�Ķ���ͱ���
		cout << "����ͼ�Ķ�������ͱߵ�������" << endl;
		cin >> vexnum >> edge;

		//�������Ķ���ͱߵ���Ϣ
		while (!check(vexnum, edge)) {
			cout << "�������ֵ���Ϸ�������������" << endl;
			cin >> vexnum >> edge;
		}

		//��ȡԴ��
		cout << "����Դ�㣺" << endl;
		cin >> source;

		//�û�ѡ��ͼ�Ĵ洢�ṹ
		cout << "������1 - 3���֣���1����ͼ�Ĵ洢�ṹΪ�ڽӾ���2����ͼ�Ĵ洢�ṹΪ�ڽ�����3����ͼ�Ĵ洢�ṹΪ�߼�����" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: {
			//�ڽӾ���
			Graph_DG graph(vexnum, edge);
			graph.createGraph();
			graph.print();
			graph.Dijkstra(source);
			graph.print_path(source);
			break;}
		case 2: {
			//�ڽ�����
			Graph_AL graph(vexnum, edge);
			graph.createGraph();
			graph.print();
			graph.Dijkstra(source);
			graph.print_path(source);
			break;}
		case 3: {
			//�ڽ�����
			Graph_EA graph(vexnum, edge);
			graph.createGraph();
			graph.print();
			graph.Dijkstra(source);
			graph.print_path(source);
			break;}
		default:
			cout << "�������" << endl;
			break;
		}
		cout << "�����˳����밴q���������������������" << endl;
		cin >> q;
	} while (q != 'q');


	system("pause");
	return 0;
}
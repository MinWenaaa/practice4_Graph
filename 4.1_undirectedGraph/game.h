//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#pragma once
#include<shader.h>
#include<graph.hpp>
#include<game_object.h>

#include<vector>


class Game {
public:
	static Game& getInstance() {				//��̬��������
		static Game instance;
		return instance;
	}
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Init(GLFWwindow* window);				//���ڳ�ʼ����������¼�
	void ProcessInput(GLfloat x, GLfloat y);	//�����������x,y�ǵ��λ�õ�����
	void update(float dt);
	void Render();								//��Ⱦ���������ƽڵ����

private:
	Game(): graphData(20), gameVertex(0), gameEdge(0), numVertex(0), numEdge(0),
		isRendering(false), color(0), nextColor(1),
		NodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), EdgeShader(Shader("../mylib/edge_basic.vs", "../mylib/edge_basic.fs")){
		std::cout << glGetError() << std::endl;
	}

	void addVertex(GLfloat x, GLfloat y);
	void addEdge(int v1, int v2);
	int targetPoint(GLfloat x, GLfloat y);

	Minw::undirectedGraph<int, int> graphData;		//�洢ͼ�Ľڵ���������Ϣ
	std::vector<painter::Node> gameVertex;				//�ڵ�ͼԪ�б�
	std::vector<painter::Edge> gameEdge;					//��ͼԪ�б�
	Shader NodeShader;								//��ͨ�Ľڵ���Ⱦ�������
	Shader EdgeShader;								//��ͨ�ı���Ⱦ�������
	bool isRendering;								//�Ƿ����ڲ��Ŷ��������ɻ�������������ֹ����
	//bool interactive;								//
	int lastPoint = -1;								//��¼�ϴ�ѡ�нڵ������
	int numVertex;									//�ڵ�����
	int numEdge;									//������
	int current_depth = -1;							//��ǰ�������
	float pocess = 0;
	GLuint color, nextColor;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);

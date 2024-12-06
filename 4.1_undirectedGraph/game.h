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
	static Game& getInstance() {				//静态单例对象
		static Game instance;
		return instance;
	}
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Init(GLFWwindow* window);				//窗口初始化，绑定鼠标事件
	void ProcessInput(GLfloat x, GLfloat y);	//处理鼠标点击，x,y是点击位置的坐标
	void update(float dt);
	void Render();								//渲染函数，绘制节点与边

private:
	Game(): graphData(20), gameVertex(0), gameEdge(0), numVertex(0), numEdge(0),
		isRendering(false), color(0), nextColor(1),
		NodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), EdgeShader(Shader("../mylib/edge_basic.vs", "../mylib/edge_basic.fs")){
		std::cout << glGetError() << std::endl;
	}

	void addVertex(GLfloat x, GLfloat y);
	void addEdge(int v1, int v2);
	int targetPoint(GLfloat x, GLfloat y);

	Minw::undirectedGraph<int, int> graphData;		//存储图的节点与链接信息
	std::vector<painter::Node> gameVertex;				//节点图元列表
	std::vector<painter::Edge> gameEdge;					//边图元列表
	Shader NodeShader;								//普通的节点渲染程序对象
	Shader EdgeShader;								//普通的边渲染程序对象
	bool isRendering;								//是否正在播放动画（生成或遍历），是则禁止交互
	//bool interactive;								//
	int lastPoint = -1;								//记录上次选中节点的坐标
	int numVertex;									//节点数量
	int numEdge;									//边数量
	int current_depth = -1;							//当前绘制深度
	float pocess = 0;
	GLuint color, nextColor;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);

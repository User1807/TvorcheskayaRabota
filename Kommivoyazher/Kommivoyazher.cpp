#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>
#include <string>

using namespace std;

class Graph
{
private:
    vector<vector<int>> matrix;
    vector<int> bestPath;
    int bestCost = numeric_limits<int>::max();

public:
    Graph(int numVertices)
    {
        matrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    int getNumVertices() { return matrix.size(); };

    void setBestPath(const vector<int>& path) { bestPath = path; }

    void setBestCost(int cost) { bestCost = cost; }

    int getBestCost() { return bestCost; }

    int getWeight(int i, int j) { return matrix[i][j]; };

    vector<int> getBestPath() { return bestPath; };

    void addEdge(int from, int to, int weight)
    {
        matrix[from][to] = weight;
        matrix[to][from] = weight;
    }

    void addVertex()
    {
        int numVertices = matrix.size();

        // Добавляем новую вершину в матрицу смежности
        for (int i = 0; i < numVertices; i++) {
            matrix[i].push_back(0);
        }

        vector<int> newRow(numVertices + 1, 0);
        matrix.push_back(newRow);
    }

    void drawCity(float x, float y, int index, bool isVisited)
    {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float radius = min(windowWidth, windowHeight) * 0.1;

        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);

        int numSegments = 100;
        float angle;
        for (int i = 0; i <= numSegments; i++) {
            angle = 2.0 * M_PI * i / numSegments;
            float dx = radius * cos(angle);
            float dy = radius * sin(angle);
            glVertex2f(x + dx, y + dy);
        }

        glEnd();

        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(x - 0.1, y - 0.1);
        string indexStr = to_string(static_cast<int>(index + 1));
        for (char c : indexStr)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }
    }

    void drawRoad(float x1, float y1, float x2, float y2, int distance, bool isVisited)
    {
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(2.0);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        glColor3f(0, 0, 1);
        float midX = (x1/0.8 + x2) / 2.1;
        float midY = (y1/0.85 + y2) / 2.1;
        glRasterPos2f(midX, midY);
        string distanceStr = to_string(static_cast<int>(distance));
        for (char c : distanceStr)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

        float size = min(windowWidth, windowHeight) * 0.5;
        float centerX = size;
        float centerY = size;

        // Отрисовка дорог
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = i + 1; j < matrix.size(); j++) {
                float angle1 = 2.0 * M_PI * i / matrix.size();
                float angle2 = 2.0 * M_PI * j / matrix.size();

                float x1 = size * cos(angle1);
                float y1 = size * sin(angle1);
                float x2 = size * cos(angle2);
                float y2 = size * sin(angle2);

                drawRoad(x1, y1, x2, y2, matrix[i][j],
                    find(bestPath.begin(), bestPath.end(), i) != bestPath.end() &&
                    find(bestPath.begin(), bestPath.end(), j) != bestPath.end());
            }
        }

        // Отрисовка городов
        for (int i = 0; i < matrix.size(); i++) {
            float angle = 2.0 * M_PI * i / matrix.size();
            float x = size * cos(angle);
            float y = size * sin(angle);
            drawCity(x, y, i, find(bestPath.begin(), bestPath.end(), i) != bestPath.end());
        }

        glFlush();
    }

    void reshape(int width, int height)
    {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

        float size = min(width, height) * 0.8;

        if (aspectRatio >= 1.0) {
            glOrtho(-size * aspectRatio, size * aspectRatio, -size, size, -1.0, 1.0);
        }
        else {
            glOrtho(-size, size, -size / aspectRatio, size / aspectRatio, -1.0, 1.0);
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
};
Graph graph(0);

void display()
{
    graph.display();
}

void reshape(int width, int height)
{
    graph.reshape(width, height);
}

void printGraph()
{
    cout << "Матрица смежности" << endl;
    for (int i = 0; i < graph.getNumVertices(); i++)
    {
        for (int j = 0; j < graph.getNumVertices(); j++)
        {
            cout << graph.getWeight(i, j) << '\t';
        }
        cout << endl;
    }
    cout << endl << endl;
}

void createGraph()
{
    int N, i, j, weight, flag = 0;

    cout << "Введите количество вершин графа: " << endl;
    cin >> N;

    while (flag != 1 && flag != 2)
    {
        cout << "Выберите способ заполнения графа" << endl;
        cout << "1. Заполнить вручную" << endl;
        cout << "2. Заполнить случайным образом" << endl;
        cin >> flag;
    }

    if (flag == 1)
    {
        for (int i = 0; i < N; i++)
        {
            graph.addVertex();
        }

        cout << "Введите данные рёбер" << endl;

        for (int i = 0; i < N-1 ; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                cout << "Начальная вершина: " << i + 1 << endl;
                cout << "Конечная вершина: " << j + 1 << endl;
                cout << "Вес ребра: ";
                cin >> weight;
                if (graph.getWeight(i, j) != 0)
                {
                    cout << "Между вершинами уже есть ребро, изменить его вес?" << endl;
                    cout << "Введите 1 чтобы изменить или другой символ чтобы продолжить без изменения" << endl;
                    cin >> flag;
                    if (flag == 1)
                    {
                        graph.addEdge(i, j, weight);
                        graph.addEdge(j, i, weight);
                        cout << "Вес ребра был изменён" << endl;
                    }
                    else N++;
                }
                else
                {
                    graph.addEdge(i, j, weight);
                    graph.addEdge(j, i, weight);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            graph.addVertex();
        }

        for (int i = 0; i < N - 1; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                graph.addEdge(i, j, rand() % 20 + 5);
            }
        }
    }
    printGraph();
}

// Функция для проверки, был ли уже посещен город
bool isVisited(int city, const vector<int>& path)
{
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == city) {
            return true;
        }
    }
    return false;
}
// Функция для нахождения наилучшего пути коммивояжера методом ветвей и границ
void solve(int current_city, vector<int>& path, int cost)
{
    if (path.size() == graph.getNumVertices()) {
        // Добавляем возвращение в начальный город
        cost += graph.getWeight(current_city, 0);
        if (cost < graph.getBestCost())
        {
            graph.setBestCost(cost);
            graph.setBestPath(path);
        }
        return;
    }

    for (int next_city = 0; next_city < graph.getNumVertices(); next_city++)
    {
        if (!isVisited(next_city, path)) {
            // Вычисляем оценку границы для данного пути
            int lower_bound = cost + graph.getWeight(current_city, next_city);
            if (lower_bound < graph.getBestCost()) {
                // Добавляем город в путь и рекурсивно ищем дальше
                path.push_back(next_city);
                solve(next_city, path, lower_bound);
                // Удаляем город из пути перед возвратом
                path.pop_back();
            }
        }
    }
}

int main(int argc, char** argv)
{
    int flag, weight;
    setlocale(LC_ALL, "ru");

    createGraph();
    vector<int> path;
    path.push_back(0); // Добавляем начальный город в путь
    solve(0, path, 0);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Задача коммивояжера");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 400, 0, 400);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    cout << "Наилучший путь коммивояжера: ";
    cout << graph.getBestPath()[graph.getNumVertices() - 1] + 1;
    for (int i = 0; i < graph.getBestPath().size(); i++) {
        cout << "->" << graph.getBestPath()[i] + 1;
    }
    cout << endl;
    cout << "Наименьшая стоимость: " << graph.getBestCost() << endl;

    glutMainLoop();
    return 0;
}
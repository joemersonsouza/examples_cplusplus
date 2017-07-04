#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

struct map{
    char value;
    map* left;
    map* right;
    map* parent;
};

queue<map*> fringe;
stack<char> path;

char getRandomValue()
{
    return char(rand()% 24+65);
}

void setElementLeft(map* elements, char value){
    elements->left = new map();
    elements->left->value = value;
    elements->left->left = NULL;
    elements->left->right = NULL;
    elements->left->parent = elements;
}

void setElementRight(map* elements, char value){
    elements->right = new map();
    elements->right->value = value;
    elements->right->left = NULL;
    elements->right->right = NULL;
    elements->right->parent = elements;
}

void recursiveElements(int limitLevel, map* elements, int level){

    if(limitLevel >= level)
        return;
    else{
        setElementLeft(elements, getRandomValue());
        setElementRight(elements, getRandomValue());
        limitLevel++;
        recursiveElements(limitLevel, elements->left, level);
        recursiveElements(limitLevel, elements->right, level);
    }
}

void initElements(map* elements){
    elements->value = 'S';
    elements->left = NULL;
    elements->right = NULL;
    elements->parent = NULL;
}

void pushFringeElements(map* elements){
    if(elements->left != NULL)
        fringe.push(elements->left);
    if(elements->right != NULL)
        fringe.push(elements->right);
}

void getPath(map* elements){
    if(elements->parent == NULL){
        cout<<"Invalid element"<<endl;
        return;
    }    
    while(elements->parent != NULL){
        path.push(elements->value);
        elements = elements->parent;
    }
    path.push('S');
}

void showGraph(map* elements){
    cout << elements->value << " "  ;
    if(elements->left != NULL)
        showGraph(elements->left);
    if(elements->right != NULL)
        showGraph(elements->right);
}

int main(){
    
    map elements;
    map* currentElement;
    char solution = 'S';
    bool found = false;
    int level = 0;
    
    initElements(&elements);
    recursiveElements(level,&elements,3);
    showGraph(&elements);

    while('S' == solution){
        cout << endl << "Choose your find path (not S): ";
        cin >> solution;
    }
    fringe.push(&elements);

    while(!fringe.empty()){
        currentElement = fringe.front();
        fringe.pop();

        if(currentElement->value == solution){
            found = true;
            getPath(currentElement);
            break;
        }
        pushFringeElements(currentElement);
    }

    if(found){
        while(!path.empty()){
            cout << path.top();
            path.pop();
        }
        cout << endl;
    }else
        cout << "Path not found!" << endl;

    return 0;
}

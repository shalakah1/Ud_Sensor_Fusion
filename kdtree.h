/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void searchHelper(Node* node, std::vector<float> target,float distanceTol,int depth,std::vector<int>&ids){
		if(node!=NULL){
			if((node->point[0]>=(target[0]-distanceTol)&&node->point[0]<=(target[0]+distanceTol))&& 
			(node->point[1]>=(target[1]-distanceTol)&&node->point[1]<=(target[1]+distanceTol))){
				float distance = sqrt((node->point[0]-target[0])*(node->point[0]-target[0])+
				(node->point[1]-target[1])*(node->point[1]-target[1]));
				if(distance<=distanceTol){
					ids.push_back(node->id);
				}
			}
			if((target[depth%2]-distanceTol)<node->point[depth%2]){
				searchHelper(node->left,target,distanceTol,depth+1,ids);
			}
			if((target[depth%2]+distanceTol)>node->point[depth%2]){
				searchHelper(node->right,target,distanceTol,depth+1,ids);
			}
		}
	}

   void insertHelper(Node** node,int depth,std::vector<float>point,int id){

		if(*node==NULL){
			*node = new Node(point, id);
		}else {
			int curr_depth=depth%2;
			if(point[curr_depth]<((*node)->point[curr_depth])){
				insertHelper(&((*node)->left),depth+1,point,id);
			}else{
				insertHelper(&((*node)->right),depth+1,point,id);
			}
		}
   } 	

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		int depth =0;
		insertHelper(&root,depth,point,id);

	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		int depth =0;
		searchHelper(root,target,distanceTol,depth,ids);
		return ids;
	}

};





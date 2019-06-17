#include "arithmeticExpression.h"

#include <iostream>
#include <sstream> //string stream
#include <fstream> //output file stream
#include <stack>
#include <string>

using namespace std;

    /* Initializes an empty tree and sets the infixExpression
    to the value of parameter passed in. */
    arithmeticExpression::arithmeticExpression(const string & val) {
        infixExpression = val; //private infixExpression variable set to val
        
        root = 0; //0 or null
    }

    /* Implementation of destrucor is optional.
       The destructor should deallocate all the nodes in the tree. */
    //~arithmeticExpression();

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
    void arithmeticExpression::buildTree() {
        string postfixExpression = infix_to_postfix(); // converts infix to postfix
        
        stack<TreeNode*> expressionTree;
        // stack is used for linking the operands/leaves to the operators/internal nodes
        
        TreeNode *child1 = 0;
        TreeNode *child2 = 0;
        
        char key = 'a';
        // increment key for the creation of the operands
        
        for (unsigned i = 0; i < postfixExpression.size(); ++i) {
            
            //if is operator pop top two nodes, make them children, and push op onto stack
            //else if is operand simply push onto stack
            if (postfixExpression.at(i) == '+' || postfixExpression.at(i) == '-' ||
            postfixExpression.at(i) == '*' || postfixExpression.at(i) == '/') {
                
                child1 = expressionTree.top(); // gets the right
                expressionTree.pop(); // pops off the stack
                child2 = expressionTree.top(); // gets the left
                expressionTree.pop(); // pops off the stack
                
                TreeNode *op = new TreeNode(postfixExpression.at(i), key + i); // creates new root of a tree or parent of the two children
                
                op->left = child2; // assigns the left operand to the new root/operator
                op->right = child1; // assigns the right operand to the new root/operator
                expressionTree.push(op); // pushes the new root to stack
            }
            else {
                TreeNode *operand = new TreeNode(postfixExpression.at(i), key + i); //creates operand as a TreeNode
                expressionTree.push(operand); // pushes new tree of operand to stack
            }
        }
    
        root = expressionTree.top(); // assigns tippity top root.
        // the last operator in the stack is set as the tippity top root of the tree
    }

    /* Calls the recursive infix function. */
    void arithmeticExpression::infix() {
        infix(root);
    }

    /* Calls the recursive prefix function. */
    void arithmeticExpression::prefix() {
        prefix(root);
    }

    /* Calls the recursive postfix function. */
    void arithmeticExpression::postfix() {
        postfix(root);
    }

void arithmeticExpression::visualizeTree(ofstream & outFS, TreeNode * n) {
    //Display all the nodes
    if (n) {
    outFS << n->key << "[ label = " << "\"" << n->data << "\"" << " ]" <<endl;
    if (n->left) {
        outFS  << n->key <<  "->" << n->left->key << "[ label = " << "\"" << n->left->data << "\"" << " ]" << endl;
        visualizeTree(outFS, n->left);
    }
    
    if (n->right) {
        outFS  << n->key << " -> " << n->right->key << "[ label =  " << "\"" << n->right->data << "\"" << " ]" << endl;
        visualizeTree(outFS, n->right);
    }
    
    outFS << endl;
    }
}
    /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the 
       beginning and ending of each expression. */
    void arithmeticExpression::infix(TreeNode *current) {
        // if current is an internal node
        if (current->left != 0 && current->right !=0) {
            cout << "(";
            
            infix(current->left); // recursively calls on the left tree branch
            
            cout << current->data; // prints out the root after the left tree branch is all printed
            
            infix(current->right); // recursively calls on the right tree branch
            
            cout << ")";
        } // else if it's a leaf. just print out the data
        else {
            cout << current->data;
        }
    }
    
    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
    void arithmeticExpression::prefix(TreeNode *current) {
        // if current is an internal node
        if (current->left != 0 && current->right != 0) {// print out the top root before anything else
            cout << current->data;
            prefix(current->left); // left tree recursion
            prefix(current->right); // right tree recursion
        }
        else {
            cout << current->data;
        }
    }

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
    void arithmeticExpression::postfix(TreeNode *current) {
        //if  current is an internal node
        if (current->left != 0 && current->right != 0) {
            
            postfix(current->left); // left branch recursion
            postfix(current->right); // right branch recursion
            
            cout << current->data; // print out the top root at the end
            
        } // else just print out the data at current
        else {
            cout << current->data;
        }
    }
    
    //======================================================================================

    int arithmeticExpression::priority(char op){
        int priority = 0;
        if(op == '('){
            priority =  3;
        }
        else if(op == '*' || op == '/'){
            priority = 2;
        }
        else if(op == '+' || op == '-'){
            priority = 1;
        }
        return priority;
    }
    
    string arithmeticExpression::infix_to_postfix(){
        stack<char> s;
        ostringstream oss;
        char c;
        for(unsigned i = 0; i< infixExpression.size();++i){
            c = infixExpression.at(i);
            if(c == ' '){
                continue;
            }
            if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
                if( c == '('){
                    s.push(c);
                }
                else if(c == ')'){
                    while(s.top() != '('){
                        oss << s.top();
                        s.pop();
                    }
                    s.pop();
                }
                else{
                    while(!s.empty() && priority(c) <= priority(s.top())){
                        if(s.top() == '('){
                            break;
                        }
                        oss << s.top();
                        s.pop();
                    }
                    s.push(c);
                }
            }
            else{ //c is an operand
                oss << c;
            }
        }
        while(!s.empty()){
            oss << s.top();
            s.pop();
        }
        return oss.str();
    }
    
    void arithmeticExpression::visualizeTree(const string &outputFilename){
        ofstream outFS(outputFilename.c_str());
        if(!outFS.is_open()){
            cout<<"Error opening "<< outputFilename<<endl;
            return;
        }
        outFS<<"digraph G {"<<endl;
        visualizeTree(outFS,root);
        outFS<<"}";
        outFS.close();
        string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
        string command = "dot -Tpng " + outputFilename + " -o " + jpgFilename;
        system(command.c_str());
    }
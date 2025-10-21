#include "ast.h"
#include <iostream>
#include <fstream>
using namespace std;

// Add a child node (pointer)
void ASTNode::addChild(ASTNode* child) {
    if (child) {
        child->parent = this;  
        children.push_back(child);
    }
}

// Add a child by name only (no lexeme)
void ASTNode::addChild(const std::string &childName) {
    ASTNode* child = new ASTNode(childName, "default");
    child->parent = this;
    children.push_back(child);
}

// Add a child by name + lexeme (for operators / identifiers)
void ASTNode::addChild(const std::string &childName, const std::string &childLexeme) {
    ASTNode* child = new ASTNode(childName, childLexeme);
    child->parent = this;
    children.push_back(child);
}

// Recursively print the AST
void ASTNode::printTree(int depth, string prefix) {
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << prefix << name;
    if (lexeme != "default" && !lexeme.empty()) cout << " : " << lexeme;
    if (type != "default" && !type.empty()) cout << " [" << type << "]";
    cout << endl;

    for (auto child : children) {
        if (child) {
            child->printTree(depth + 1);
        }
    }
}

// Generate DOT format for Graphviz
void ASTNode::generateDOT(ofstream& out, int& nodeId) {
    int currentId = nodeId++;
    out << "  node" << currentId << " [label=\"" << name;
    if (lexeme != "default" && !lexeme.empty()) out << "\\n" << lexeme;
    if (type != "default" && !type.empty()) out << "\\n[" << type << "]";
    out << "\"];" << endl;

    for (auto child : children) {
        if (child) {
            int childId = nodeId;
            child->generateDOT(out, nodeId);
            out << "  node" << currentId << " -> node" << childId << ";" << endl;
        }
    }
}

// Type helper stubs (keep for compatibility)
void setDeclarationType(ASTNode* node, const std::string &type) {
    if (node) node->setType(type);
}

std::string setDeclaratorType(ASTNode* node, const std::string &type, bool isFunctionDefinition, int isVirtual) {
    if (node) node->setType(type);
    return type;
}

std::string setDirectDeclaratorType(ASTNode* node, const std::string &type, bool isFunctionDefinition, int isVirtual) {
    if (node) node->setType(type);
    return type;
}

std::string setAbstractDirectDeclaratorType(ASTNode* node, const std::string &type) {
    if (node) node->setType(type);
    return type;
}

std::string setAbstractDeclaratorType(ASTNode* node, const std::string &type) {
    if (node) node->setType(type);
    return type;
}
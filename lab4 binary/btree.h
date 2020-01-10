#pragma once

#include <memory.h>
#include <stack>
#include <string.h>
#include <iostream>
#include <cstring>

// Nodes of binary tree functions
namespace BT_Nodes
{
	template <typename Item>
	struct		Node
	{
		Node	*left;
		Node	*right;
		Item	data;
	};

	// Creating of new node with that data
	template <typename Item>
	Node<Item>*		new_node(Item data)
	{
		Node<Item>*	node;

		node = new Node<Item>;
		node->data = data;
		node->left = nullptr;
		node->right = nullptr;
		return (node);
	}

	// Deleting of node with function del_callback, wich takes an pointer to data
	template <typename Item>
	void			delete_node(Node<Item>* node, void (*del_callback)(Item *data))
	{
		del_callback(&node->data);
		delete node;
	}

	// Deleting full tree with function del_callback, wich takes an pointer to data
	template <typename Item>
	void			delete_tree(Node<Item>* node, void (*del_callback)(Item *data))
	{
		if (!node)
			return ;
		delete_tree(node->left, del_callback);
		delete_tree(node->right, del_callback);
		del_callback(&node->data);
		delete node;
	}

	// Outputs a nodes content
	template <typename Item>
	void			put_node(Node<Item>* node);
}

template <typename Item>
void	no_free(Item *ptr)
{
	ptr = nullptr;
}

template <typename Item>
class			BinaryTree
{
	protected:
		BT_Nodes::Node<Item>	*root;
		void					(*del_callback)(Item *data);

	public:
					BinaryTree(void (*del_callback)(Item *data) =&no_free);
					~BinaryTree(void);
};

template <typename Item>
BinaryTree<Item>::BinaryTree(void (*del_callback)(Item *data))
{
	this->del_callback = del_callback;
	this->root = nullptr;
}

template <typename Item>
BinaryTree<Item>::~BinaryTree(void)
{
	BT_Nodes::delete_tree<Item>(this->root, this->del_callback);
	this->root = nullptr;
}

enum 	ASTtype
{
	nul,
	operation,
	number,
	brkts_op
};

struct		AST_data
{
	ASTtype		type;
	union
	{
		char	oper;
		long	value;
	};
};

using namespace std;
using namespace BT_Nodes;

class		ASTree: public BinaryTree<AST_data>
{
	private:
		size_t		add_number(stack<Node<AST_data> *>* stk, size_t i, const char *expr, Node<AST_data>** nd);
		size_t		add_op(stack<Node<AST_data> *>* stk, size_t i, const char *expr, Node<AST_data>** nd);
		size_t		subtree(stack<Node<AST_data> *>* stk, size_t i, const char *expr, Node<AST_data>** nd);
		size_t		skip_space(size_t i, const char *expr);
		size_t		tinder(const char *expr);
		bool		isop(char ch)
		{
			return (ch == '+' || ch == '*' || ch == '-');
		};
		Node<AST_data>*		parse_expr(const char *expr);
		long				resolver(Node<AST_data> *ls);
		Node<AST_data>*		copy_tree(Node<AST_data> *ls);
		char				expr_or[1024];
		
	public:
		ASTree(void (*del_callback)(AST_data *data)=&no_free<AST_data>)
		{
			bzero(this->expr_or, sizeof(this->expr_or));
			this->del_callback = del_callback;
			this->root = nullptr;
		};
		ASTree(const char *expr, void (*del_callback)(AST_data *data)=&no_free<AST_data>)
		{
			this->del_callback = del_callback;
			this->root = parse_expr(expr);
			strncpy(this->expr_or, expr, sizeof(this->expr_or));
		};
		ASTree(ASTree* AST)
		{
			strncpy(this->expr_or, AST->expr_or, sizeof(this->expr_or));
			this->root = copy_tree(AST->root);
			this->del_callback = AST->del_callback;
		};
		long				execute(void);
		void				prepare(const char *extr);
		void				console_log(void);
		void				put_formula(void)
		{
			if (this->expr_or[0])
				std::cout << "FORMULA: " << this->expr_or << "\n";
			else
				std::cout << "No formula yet\n";
		}

};

void		ASTree::prepare(const char *extr)
{
	if (this->root)
		delete_tree(this->root, this->del_callback);
	this->root = parse_expr(extr);
	strncpy(this->expr_or, extr, sizeof(this->expr_or));
}

long		ASTree::execute(void)
{
	if (this->root == nullptr)
		throw ("NO PREPARED EXPRESSION");
	return (resolver(this->root));
}

Node<AST_data>*		ASTree::copy_tree(Node<AST_data> *ls)
{
	Node<AST_data>*	node;

	if (ls == nullptr)
		return (nullptr);
	node = new_node(ls->data);
	node->left = copy_tree(ls->left);
	node->right = copy_tree(ls->right);
	return (node);
}

long		ASTree::resolver(Node<AST_data> *nd)
{
	if (nd == nullptr)
		throw ("EXECUTE ERROR OCCURED");
	if (nd->data.type == number)
		return (nd->data.value);
	if (nd->data.type == operation || nd->data.type == brkts_op)
	{
		switch (nd->data.oper)
		{
		case '+':
			return (resolver(nd->left) + resolver(nd->right));
		case '-':
			return (resolver(nd->left) - resolver(nd->right));
		case '*':
			return (resolver(nd->left) * resolver(nd->right));
		default:
			throw ("EXECUTE ERROR OCCURED");
		}
	}
	throw ("EXECUTE ERROR OCCURED");
	return (0);
}

size_t		ASTree::add_number(stack<Node<AST_data> *>* stk, size_t i, const char *expr, Node<AST_data>** nd)
{
	long 			num = atol(expr + i);
	AST_data		data;
	Node<AST_data>	*node;

	data.type = number;
	data.value = num;
	node = new_node<AST_data>(data);
	if (expr[i] == '-')
		++i;
	for (;isdigit(expr[i]); ++i)
		;
	if (*nd == nullptr)
		*nd = node;
	else if ((*nd)->data.type == operation)
		(*nd)->right = node;
	else
		throw (num);
	return (i);
}

size_t		ASTree::add_op(stack<Node<AST_data> *>* stk, size_t i, const char *expr, Node<AST_data>** nd)
{
	AST_data		data;
	Node<AST_data>	*node;
	Node<AST_data>	*numi;
	char			o_op;

	data.type = operation;
	data.oper = expr[i];
	node = new_node<AST_data>(data);
	o_op = (*nd)->data.oper;
	if (*nd == nullptr)
		throw (expr[i]);
	else if ((*nd)->data.type == operation && expr[i] == '*')
	{
		//downwalk
		if ((*nd)->right == nullptr)
			throw (expr[i]);
		stk->push(*nd);
		numi = (*nd)->right;
		if (numi->data.type != number)
			throw (expr[i]);
		node->left = numi;
		(*nd)->right = node;
		*nd = node;
	}
	else if ((*nd)->data.type != nul)
	{
		while (stk->size())
		{
			*nd = stk->top();
			stk->pop();
		}
		node->left = *nd;
		*nd = node;
	}
	else
		throw (expr[i]);
	return (i + 1);
}

size_t		ASTree::skip_space(size_t i, const char *expr)
{
	for (;expr[i] == ' '; ++i)
		;
	return (i);
}

size_t		ASTree::tinder(const char *expr)
{
	size_t	i = 0;
	int		brks = 0;

	do
	{
		if (!expr[i])
			throw('(');
		if (expr[i] == '(')
			++brks;
		if (expr[i] == ')')
			--brks;
		++i;
	}
	while (brks > 0);
	if (brks < 0)
		throw (')');
	return (i);
}

size_t		ASTree::subtree(stack<Node<AST_data> *>* stk, size_t i, const char *expr, Node<AST_data>** nd)
{
	size_t			len = this->tinder(expr + i);
	char			*str = strndup(expr + i + 1, len - 2);
	Node<AST_data>	*node = this->parse_expr(str);

	i += len;
	node->data.type == operation ? node->data.type = brkts_op : 0;
	delete str;
	if (*nd == nullptr)
		*nd = node;
	else if ((*nd)->data.type == operation)
		(*nd)->right = node;
	else
		throw ('(');
	return (i);
}

Node<AST_data>*	ASTree::parse_expr(const char *expr)
{
	size_t					i;
	stack<Node<AST_data> *>	stk;
	Node<AST_data>	*nd = nullptr;

	for (i = 0; expr[i];)
	{
		if (isdigit(expr[i]) || (expr[i] == '-' && isdigit(expr[i + 1])))
			i = this->add_number(&stk, i, expr, &nd);
		else if (isop(expr[i]))
			i = this->add_op(&stk, i, expr, &nd);
		else if (expr[i] == ' ')
			i = this->skip_space(i, expr);
		else if (expr[i] == '(')
			i = this->subtree(&stk, i, expr, &nd);
		else
			throw (expr[i]);
	}
	while (stk.size())
	{
		nd = stk.top();
		stk.pop();
	}
	return (nd);
}

size_t			put_ast_node(AST_data nd, bool isend)
{
	size_t		printed;

	if (nd.type == operation || nd.type == brkts_op)
	{
		cout << nd.oper;
		printed = 1;
	}
	else if (nd.type == number)
	{
		cout << nd.value;
			printed = 1;
		for (;nd.value > 9;nd.value /= 10)
			printed += 1;
	}
	if (!isend)
	{
		cout << " => ";
		printed += 4;
	}
	return (printed);
}

void			put_the_tree(Node<AST_data> *nd, size_t u, size_t pr)
{
	size_t		addit;

	if (nd == nullptr)
		return ;

	for (size_t	i = 0; i < u; ++i)
		cout << " ";
	addit = put_ast_node(nd->data, !nd->right);
	if (!nd->right) cout << "\n";
	if (!nd->right) pr = 0;
	put_the_tree(nd->right, !nd->right ? pr : 0, pr + addit);
	put_the_tree(nd->left, pr, pr);
}

void			ASTree::console_log(void)
{
	put_the_tree(this->root, 0, 0);
}

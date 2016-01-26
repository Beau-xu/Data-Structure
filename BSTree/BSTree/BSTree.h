#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

//����������Ľڵ�ṹ
template <typename T>
struct BSNode
{
	BSNode(T t)
	: value(t), lchild(nullptr), rchild(nullptr){}
	
	BSNode() = default;

	T value;
	BSNode<T>* lchild;
	BSNode<T>* rchild;
	BSNode<T>* parent;
};

//�����������
template <typename T>
class BSTree
{
public:
	BSTree();
	~BSTree(){};

	void preOrder();	//ǰ�����������
	void inOrder();		//�������������
	void postOrder();	//�������������
	void layerOrder();	//��α���������

	BSNode<T>* search_recursion(T key);		//�ݹ�ؽ��в���
	BSNode<T>* search_Iterator(T key);		//�����ؽ��в���

	T search_minimun(); //������СԪ��
	T search_maximum(); //�������Ԫ��

	BSNode<T>* successor  (BSNode<T>* x);	//����ָ���ڵ�ĺ�̽ڵ�
	BSNode<T>* predecessor(BSNode<T>* x);	//����ָ���ڵ��ǰ���ڵ�

	void insert(T key);	//����ָ��ֵ�ڵ�
	void remove(T key);	//ɾ��ָ��ֵ�ڵ�
	void destory();		//���ٶ�����
	void print();		//��ӡ������


private:
	BSNode<T>* root; //���ڵ�
private:
	BSNode<T>* search(BSNode<T>* & p, T key); //���Һ��������ݹ����
	void remove(BSNode<T>*  p, T key);		  //ɾ���ڵ�
	
};

/*Ĭ�Ϲ��캯��*/
template <typename T>
BSTree<T>::BSTree() :root(nullptr){};

/*���뺯��*/
template <typename T>
void BSTree<T>::insert(T key)
{
	BSNode<T>* pparent = nullptr;
	BSNode<T>* pnode = root;

	while (pnode != nullptr)		//Ѱ�Һ��ʵĲ���λ��
	{
		pparent = pnode;
		if (key > pnode->value)
			pnode = pnode->rchild;
		else if (key < pnode->value)
			pnode = pnode->lchild;
		else
			break;
	}

	pnode = new BSNode<T>(key);
	if (pparent == nullptr)			//����ǿ���
	{
		root = pnode;				//���½ڵ�Ϊ��
	}
	else
	{
		if (key > pparent->value)	
		{
			pparent->rchild = pnode;//�����½ڵ�Ϊ�丸�ڵ����
		}
		else
			pparent->lchild = pnode;//���Һ�
	}
	pnode->parent = pparent;		//ָ���½ڵ�ĸ��ڵ�

};

/*����ָ��Ԫ�صĽڵ㣨�ǵݹ飩*/
template <typename T>
BSNode<T>* BSTree<T>::search_Iterator(T key)
{
	BSNode<T> * pnode = root;
	while (pnode != nullptr)
	{
		if (key == pnode->value)	//�ҵ�
			return pnode;
		if (key > pnode->value)		//�ؼ��ֱȽڵ�ֵ���ڽڵ�����������
			pnode = pnode->rchild;
		else
			pnode = pnode->lchild; //�ؼ��ֱȽڵ�ֵС���ڽڵ�����������
	}
	return nullptr;
};

/*����ָ��Ԫ�صĽڵ㣨�ݹ飩*/
template <typename T>
BSNode<T>* BSTree<T>::search_recursion(T key)
{
	return search(root, key);		
};

/*private:search()*/
/*�ݹ���ҵ����ڲ�ʵ��*/

template <typename T>
BSNode<T>* BSTree<T>::search(BSNode<T>* & pnode, T key)
{
	if (pnode == nullptr)
		return nullptr;
	if (pnode->value == key)
		return pnode;
	cout << "-->" << pnode->value << endl; //�����������·��
	if (key > pnode->value)
		return search(pnode->rchild, key);
	return search(pnode->lchild, key);
};

/*ɾ��ָ���ڵ�*/
template <typename T>
void BSTree<T>::remove(T key)
{
	remove(root, key);
};
/*ɾ��ָ���ڵ�*/
/*�ڲ�ʹ�ú���*/
template <typename T>
void BSTree<T>::remove(BSNode<T>* pnode, T key)
{
	if (pnode != nullptr)
	{
		if (pnode->value == key)
		{
			BSNode<T>* pdel=nullptr;
			//ȷ��Ҫɾ�������ĸ��ڵ�
			if (pnode->lchild == nullptr || pnode->rchild == nullptr)
				pdel = pnode;	
			else
				pdel = predecessor(pnode);

			//Ҫɾ���Ľڵ�ֻ��һ�����ӣ�����û�к��ӣ������ҳ��亢�ӵ�ָ��
			BSNode<T>* pchild=nullptr;
			if (pdel->lchild != nullptr)
				pchild = pdel->lchild;
			else
				pchild = pdel->rchild;

			//���亢��ָ��ɾ���ڵ�ĸ��ڵ�
			if (pchild != nullptr)
				pchild->parent = pdel->parent;


			if (pdel->parent == nullptr) //���Ҫɾ���Ľڵ���ͷ�ڵ�
				root = pchild;			 //����ڵ� Ҫ�ı�

			else if (pdel->parent->lchild==pdel)
			{
				pdel->parent->lchild = pchild;
			}
			else
			{
				pdel->parent->rchild = pchild;
			}


			if (pnode->value != pdel->value)
				pnode->value = pdel->value;
			delete pdel;
		}
		//���еݹ�ɾ��
		else if (key > pnode->value)
		{
			remove(pnode->rchild, key);
		}
		else remove(pnode->lchild, key);
	}
};
/*Ѱ����ǰ���ڵ�*/
/*
һ���ڵ��ǰ���ڵ���3�������
1. �����������������������ڵ�Ϊ��ǰ���ڵ�
2. ��û������������������Ϊ�����������丸�ڵ�Ϊ��ǰ���ڵ�
3. ��û������������������Ϊ��������������ǰ���ڵ�Ϊ����һ��ӵ���������ĸ��ڵ㡱
*/
template <typename T>
BSNode<T>* BSTree<T>::predecessor(BSNode<T>* pnode)
{
	if (pnode->lchild != nullptr)
	{
		pnode = pnode->lchild;
		while (pnode->rchild != nullptr)
		{
			pnode = pnode->rchild;
		}
		return pnode;
	}

	BSNode<T>* pparent = pnode->parent;
	while (pparent != nullptr && pparent->lchild == pnode)//�������ѭ�������ǵ��������������Ϊ�ڶ������
	{
		pnode = pparent;
		pparent = pparent->parent;
	}
	return pparent;
};

/*Ѱ�����̽ڵ�*/
/*
һ�����к�̽ڵ�������
1. �����������������̽ڵ�Ϊ��������������ڵ�
2. ��û��������������������һ�����ӣ����̽ڵ�Ϊ����˫��
3. ��û��������������������һ���Һ��ӣ������̽ڵ�Ϊ���������ӵ�������ڵ㡱
*/
template <typename T>
BSNode<T>* BSTree<T>::successor(BSNode<T>* pnode)
{
	if (pnode->rchild != nullptr)
	{
		pnode = pnode->rchild;
		while (pnode->lchild != nullptr)
		{
			pnode = pnode->lchild;
		}
		return pnode;
	}

	BSNode<T>* pparent = pnode->parent;
	while (pparent!=nullptr&& pparent->rchild == pnode)
	{
		pnode = pparent;
		pparent = pparent->parent;
	}
	return pparent;
};

#endif 
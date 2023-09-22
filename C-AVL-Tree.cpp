#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Poin {
	int number;
	Poin *left;
	Poin *right;
	int height;
};

int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int height(Poin* hint){
	if(hint == NULL){
		return 0;
	}
	return hint->height;
}

Poin* createPoin(int number){
	Poin* newPoin = (Poin*)malloc(sizeof(Poin));
	newPoin->number = number;
	newPoin->left = NULL;
	newPoin->right = NULL;
	newPoin->height = 1;
	return newPoin;
}

Poin *rRotate(Poin *root){
	Poin *left = root->left;
	Poin *leftRight = left->right;
	root->left = leftRight;
	left->right = root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	left->height = max(height(left->left), height(left->right)) + 1;
	
	return left;
}

Poin *lRotate(Poin *root){
	Poin *right = root->right;
	Poin *rightLeft = right->left;
	root->right = rightLeft;
	right->left = root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	right->height = max(height(right->left), height(right->right)) + 1;
	
	return right;
}

Poin* inserts(Poin* hint, int number){
	if(hint == NULL){
		return createPoin(number);
	}
	
	if(number > hint->number){
		hint->right = inserts(hint->right, number);
	}else{
		hint->left = inserts(hint->left, number);
	}
	
	hint->height = max(height(hint->left), height(hint->right)) + 1;
	
	int balancing = height(hint->left) - height(hint->right);
	
	if(balancing > 1 && number < hint->left->number){
		return rRotate(hint);
	}
	
	if(balancing < -1 && number < hint->right->number){
		hint->right = rRotate(hint->right);
		return lRotate(hint);
	}
	
	if(balancing > 1 && number > hint->left->number){
		hint->left = lRotate(hint->left);
		return rRotate(hint);
	}
	
	if(balancing < -1 && number > hint->right->number){
		return lRotate(hint);
	}
	
	return hint;
}

Poin* remove(Poin* hint, int number){
	if(hint == NULL){
		return NULL;
	}
	if(number < hint->number){
		hint->left = remove(hint->left, number);
	}else if(number > hint->number){
		hint->right = remove(hint->right, number);
	}else{
		if(hint->right == NULL && hint->left ==  NULL){
			free(hint);
			hint = NULL;
		}else if(hint->right == NULL && hint->left != NULL){
			Poin* change = hint->left;
			*hint = *change;
			free(change);
			change = NULL;
		}else if(hint->right != NULL && hint->left == NULL){
			Poin* change = hint->right;
			*hint = *change;
			free(change);
			change = NULL;
		}else if(hint->right != NULL && hint->left != NULL){
			Poin* change = hint->left;
			while(change->right != NULL){
				change = change->right;
			}
			
			hint->number = change->number;
			hint->left = remove(hint->left, change->number);
		}
	}
	
	if(hint == NULL){
		return hint;
	}
	
	hint->height = max(height(hint->left), height(hint->right)) + 1;
	
	int balance = height(hint->left) - height(hint->right);
	
	if(balance > 1 && number < hint->left->number){
		return rRotate(hint);
	}
	
	if(balance < -1 && number > hint->right->number){
		return lRotate(hint);
	}
	
	if(balance > 1 && number > hint->left->number){
		hint->left = lRotate(hint->left);
		return rRotate(hint);
	}
	
	if(balance < -1 && number < hint->right->number){
		hint->right = rRotate(hint->right);
		return lRotate(hint);
	}
	return hint;
}

void InOrder(Poin* root){
	if(root != NULL){
		InOrder(root->left);
		printf("%d ", root->number);
		InOrder(root->right);
	}
}

void PreOrder(Poin* root){
	if(root != NULL){
		printf("%d ", root->number);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

void PostOrder(Poin* root){
	if(root != NULL){
		PostOrder(root->left);
		PostOrder(root->right);
		printf("%d ", root->number);
	}
}

struct Poin *findnode(Poin *root, int number) {
	if(root == NULL) {
		return (NULL);
	}else if(number < root->number) {
		findnode(root->left, number);
	}else if(number > root->number) {
		findnode(root->right, number);
	}else if(number == root->number) {
		return(root);
	}
}


int main () {
	Poin *root = NULL;
	
//	root = inserts(root, 6);
//	root = inserts(root, 27);
//	root = inserts(root, 19);
//	root = inserts(root, 11);
//	root = inserts(root, 36);
//	root = inserts(root, 14);
//	root = inserts(root, 81);
//	root = inserts(root, 63);
//	root = inserts(root, 75);
	
	mainmenu:
		int nomor;
		do{
			system("cls");
            printf("1. Insertion\n");
            printf("2. Deletion\n");
            printf("3. Transversal\n");
            printf("4. Exit\n");
            printf("Choose: ");

            scanf(" %d", &nomor);
			
		}while(nomor < 1 || nomor > 4);

	
	
	switch(nomor)
	{
		case 1:
			int tempNumber;
			printf("Insert: ");
			scanf("%d", &tempNumber);
			root = inserts(root, tempNumber);
			getchar();
			printf("\nEnter to Continue...");
			getchar(); goto mainmenu;
			break;
		
		case 2:
			int delNumber;
			printf("Delete: ");
			scanf("%d", &delNumber);
			if(findnode(root, delNumber) == NULL) {
				printf("Data Not Found");
			}else {
				root = remove(root, delNumber);
				printf("Value %d was deleted", delNumber);
			}
			getchar();
			printf("\nEnter to Continue...");
			getchar(); goto mainmenu;
			break;
		
		case 3:
			printf("Preorder : ");
			PreOrder(root);
			printf("\n");
			printf("Inorder : ");
			InOrder(root);
			printf("\n");
			printf("Postorder : ");
			PostOrder(root);
			getchar();
			printf("\nEnter to Continue...");
			getchar(); goto mainmenu;
			break;
		
		case 4:
			printf("Thank you");
			break;
	}
}





#include "Header.h"

int main(void)
{
    Node* Plist = NULL;
    main_menu(&Plist);

    // Free allocated memory
    Node* pCur = Plist;
    while (pCur != NULL)
    {
        Node* pTemp = pCur;
        pCur = pCur->pNext;
        free(pTemp);
    }

    return 0;
}

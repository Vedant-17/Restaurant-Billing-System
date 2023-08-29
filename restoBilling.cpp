#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

struct items
{

    char item[20];
    float price;
    int qty;
};

struct orders
{

    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30])
{
    cout << "\n\n";
    cout << "\t     Vedant's Restaurant";
    cout << "\n\t    ---------------------";
    cout << "\nDate: " << date;
    cout << "\nInvoice To: " << name;
    cout << "\n";
    cout << "-------------------------------------\n";
    cout << "Items\t\t";
    cout << "Qty\t\t";
    cout << "Total\t\t";
    cout << "\n-------------------------------------";
    cout << "\n\n";
}
void generateBillBody(char item[30], int qty, float price)
{
    cout << item;
    cout << "\t\t" << qty;
    cout << "\t\t" << qty * price;
    cout << "\n";
}

void generateBillFooter(float total)
{
    cout << "\n";
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst;
    cout << "--------------------------------------\n";
    cout << "Sub Total\t\t\t" << total;
    cout << "\nDiscount @10%\t\t\t" << dis;
    cout << "\n\t\t\t\t------";
    cout << "\nNet Total\t\t\t" << netTotal;
    cout << "\nCGST @9%\t\t\t" << cgst;
    cout << "\nSGST @9%\t\t\t" << cgst;
    cout << "\n----------------------------------------";
    cout << "\nGrand Total\t\t\t" << grandTotal;
    cout << "\n----------------------------------------\n";
}

int main()
{
    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contflag = 'y';
    char name[50];
    FILE *fp;
    while (contflag == 'y')
    {
        system("cls");
        float total = 0;
        int invoiceFound = 0;
        cout << "\t===========VEDANT's RESTAURANT===========";
        cout << "\n\nPlease select your preferred option: ";
        cout << "\n\n1.Generate Invoice";
        cout << "\n2.Show all Invoices";
        cout << "\n3.Search Invoice";
        cout << "\n4.Exit";

        cout << "\n\nYour Choice: ";
        cin >> opt;
        fgetc(stdin);
        switch (opt)
        {
        case 1:
            system("cls");
            cout << "\nPlease enter the name of the customer:\t ";
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);
            // cin >> ord.customer;
            cout << "\nPlease enter the number of items:\t";
            cin >> n;
            ord.numOfItems = n;

            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                cout << "\n\n";
                cout << "Please enter the item " << i + 1 << "\t";
                fgets(ord.itm[i].item, 20, stdin);
                // cin >> ord.itm[i].item;
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                cout << "Please enter the quantity:\t";
                cin >> ord.itm[i].qty;
                cout << "Please enter the unit price:\t";
                cin >> ord.itm[i].price;
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);
            cout << "\nDo you want to save the invoice[y/n]\t";
            cin >> saveBill;

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                {
                    cout << "\nSuccessfully saved";
                }
                else
                {
                    cout << "\nError Saving";
                }
                fclose(fp);
            }

            break;
        case 2:
            system("cls");
            fp = fopen("RestaurantBill.dat", "r");
            cout << "\n *****Your Previous Invoices*****\n";
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;
        case 3:
            cout << "\nEnter the name of the customer:\t";
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
                system("cls");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\t *****Invoice of %s *****", name);
                while (fread(&order, sizeof(struct orders), 1, fp))
                {
                    float tot = 0;
            
                    if (!strcmp(order.customer, name))
                    {
                        generateBillHeader(order.customer, order.date);
                        for (int i = 0; i < order.numOfItems; i++)
                        {
                            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        generateBillFooter(total);
                        invoiceFound = 1;
                    }
                }
                if (!invoiceFound)
                {
                    printf("Sorry the invoice for %s does not exists", name);
                }
                fclose(fp);
                break;
            case 4:
                cout << "\n\t\t Thank you :)\n\n";
                exit;
            default:
                cout << "Invalid Option";
                break;
            }
            cout << "\nDo you want to perform another operation?[y/n] ";
            cin >> contflag;
        }
        cout << "\n\n";
        cout << "\n\t\t Thank you :)\n\n";
        cout << "\n\n";
        return 0;
    }
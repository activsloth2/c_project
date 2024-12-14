#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure to represent an expense
struct Expense {
    char category[50];
    char description[100];
    float amount;
};

// Global variables
float Sum = 0;
float totalEMI = 0; // To store the total monthly EMI

// Function to add an expense
void addExpense(struct Expense expenses[], int *numExpenses) {
    printf("Enter the category: ");
    scanf("%s", expenses[*numExpenses].category);
    printf("Enter the description: ");
    scanf("%s", expenses[*numExpenses].description);
    printf("Enter the amount: ");
    scanf("%f", &expenses[*numExpenses].amount);
    Sum += expenses[*numExpenses].amount;
    (*numExpenses)++;
}

// Function to view all expenses
void viewAllExpenses(float income, struct Expense expenses[], int numExpenses) {
    if (numExpenses == 0) {
        printf("No expenses recorded.\n");
        return;
    }
    printf("\nAll Expenses:\n");
    printf("Category\tExpense\t\tAmount\n");
    for (int i = 0; i < numExpenses; i++) {
        printf("%-20s%-20s%-10.2f\n", expenses[i].category, expenses[i].description, expenses[i].amount);
    }
    printf("Total Income: %.2f\n", income);
    printf("Total Expenditure: %.2f\n", Sum);
    printf("Total Monthly EMI: %.2f\n", totalEMI);
    printf("Amount Left: %.2f\n", income - (Sum + totalEMI));
}

// Function to calculate EMI
void calculateEMI() {
    char emiCategory[50];
    float principal, rate, time, emi;

    printf("Enter the EMI category: ");
    scanf("%s", emiCategory);
    printf("Enter the loan amount (principal): ");
    scanf("%f", &principal);
    printf("Enter the annual interest rate (in percentage): ");
    scanf("%f", &rate);
    printf("Enter the time period (in years): ");
    scanf("%f", &time);

    float monthlyRate = rate / (12 * 100);
    float months = time * 12;
    emi = (principal * monthlyRate * pow(1 + monthlyRate, months)) / (pow(1 + monthlyRate, months) - 1);

    printf("Monthly EMI for %s: %.2f\n", emiCategory, emi);
    totalEMI += emi; // Add the EMI to the total monthly EMI
}

// Function to plot data for income, expenditure, and EMI
void plotData(float income, float expenditure, float emi) {
    FILE *dataFile = fopen("data.txt", "w");
    if (dataFile == NULL) {
        printf("Error opening file for plotting!\n");
        return;
    }

    // Write data for plotting
    fprintf(dataFile, "Income %.2f\n", income);
    fprintf(dataFile, "Expenditure %.2f\n", expenditure);
    fprintf(dataFile, "EMI %.2f\n", emi);
    fclose(dataFile);

    // Generate the gnuplot script
    FILE *gnuplotScript = fopen("plot.gnuplot", "w");
    if (gnuplotScript == NULL) {
        printf("Error creating gnuplot script!\n");
        return;
    }

    fprintf(gnuplotScript,
            "set terminal png size 800,600\n"
            "set output 'data.png'\n"
            "set title 'Income, Expenditure, and EMI'\n"
            "set style data histograms\n"
            "set style fill solid\n"
            "set boxwidth 0.5\n"
            "set ylabel 'Amount'\n"
            "set xlabel 'Category'\n"
            "plot 'data.txt' using 2:xtic(1) title '' with histogram\n");

    fclose(gnuplotScript);

    // Execute gnuplot command
    system("gnuplot plot.gnuplot");
    printf("Plot saved as 'data.png'\n");
}

// Function to plot expenses by category
void plotExpenses(struct Expense expenses[], int numExpenses) {
    if (numExpenses == 0) {
        printf("No expenses to plot.\n");
        return;
    }

    FILE *expensesFile = fopen("expenses.txt", "w");
    if (expensesFile == NULL) {
        printf("Error opening file for expenses plotting!\n");
        return;
    }

    // Write expense data by category
    for (int i = 0; i < numExpenses; i++) {
        fprintf(expensesFile, "%s %.2f\n", expenses[i].category, expenses[i].amount);
    }
    fclose(expensesFile);

    // Generate gnuplot script for expenses
    FILE *gnuplotScript = fopen("expenses.gnuplot", "w");
    if (gnuplotScript == NULL) {
        printf("Error creating gnuplot script for expenses!\n");
        return;
    }

    fprintf(gnuplotScript,
            "set terminal png size 800,600\n"
            "set output 'expenses.png'\n"
            "set title 'Expenses by Category'\n"
            "set style data histograms\n"
            "set style fill solid\n"
            "set boxwidth 0.5\n"
            "set ylabel 'Amount'\n"
            "set xlabel 'Category'\n"
            "plot 'expenses.txt' using 2:xtic(1) title '' with histogram\n");

    fclose(gnuplotScript);

    // Execute gnuplot command
    system("gnuplot expenses.gnuplot");
    printf("Expenses plot saved as 'expenses.png'\n");
}

int main() {
    struct Expense expenses[100]; // Assume a maximum of 100 expenses
    int numExpenses = 0;
    int choice;
    float income;

    printf("Enter your income: ");
    scanf("%f", &income);

    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. Calculate EMI\n");
        printf("3. View All Expenses\n");
        printf("4. Plot Income, Expenditure, and EMI\n");
        printf("5. Plot Expenses by Category\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense(expenses, &numExpenses);
                break;
            case 2:
                calculateEMI();
                break;
            case 3:
                viewAllExpenses(income, expenses, numExpenses);
                break;
            case 4:
                plotData(income, Sum, totalEMI);
                break;
            case 5:
                plotExpenses(expenses, numExpenses);
                break;
            case 6:
                printf("\nExiting the Expense Tracker.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}

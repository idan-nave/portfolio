package bank;

import java.util.InputMismatchException;
import java.util.Scanner;

public class BankingApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Bank bank = new Bank(100000); // Bank starts with $100,000 in reserves

        Client client1 = new Client("John Doe");
        Account account1 = new Account("Checking Account", 5000);
        Account account2 = new Account("Savings Account", 2000);
        client1.addAccount(account1);
        client1.addAccount(account2);
        bank.addAccount(account1);
        bank.addAccount(account2);

        while (true) {
            // System.out.println("\nBanking System");
            // System.out.println("1. Deposit");
            // System.out.println("2. Withdraw");
            // System.out.println("3. Take Loan");
            // System.out.println("4. View Account Balance");
            // System.out.println("5. View Account Loan Details");
            // System.out.println("6. Apply Monthly Commission");
            // System.out.println("7. View Bank Details");
            // System.out.println("8. View Client Details");
            // System.out.println("9. Exit");
            // System.out.print("Choose an option: ");

            // Display the menu options in 3 columns
            System.out.println("\nBanking System\n");
            System.out.printf("%-30s%-30s%-30s%n", "1. Deposit", "2. Withdraw", "3. Take Loan");
            System.out.printf("%-30s%-30s%-30s%n", "4. View Account Balance", "5. View Account Loan Details",
                    "6. Apply Monthly Commission");
            System.out.printf("%-30s%-30s%-30s%n", "7. View Bank Details", "8. View Client Details", "9. Exit");
            System.out.print("\nChoose an option: ");

            try {
                int choice = scanner.nextInt(); // Read user choice

                // Process user choice based on input
                switch (choice) {
                    case 1:
                        System.out.print("Enter amount to deposit: ");
                        double depositAmount = scanner.nextDouble();
                        if (account1.deposit(depositAmount))
                            System.out.println("Deposited: " + depositAmount);
                        break;

                    case 2:
                        System.out.print("Enter amount to withdraw: ");
                        double withdrawAmount = scanner.nextDouble();
                        if (account1.withdraw(withdrawAmount))
                            System.out.println("Withdrew: " + withdrawAmount);
                        break;

                    case 3:
                        System.out.print("Enter loan amount: ");
                        double loanAmount = scanner.nextDouble();
                        if (client1.takeLoan(bank, loanAmount))
                            System.out.println("Loan of " + loanAmount + " granted.");
                        break;

                    case 4:
                        System.out.println(account1.toString());
                        break;

                    case 5:
                        System.out.println("Account Loan Details: ");
                        System.out.println("Loan Debt: $" + account1.getBalance());
                        break;

                    case 6:
                        bank.collectCommissions(0.01); // Apply 1% monthly commission
                        System.out.println("Applied monthly commission to all accounts.");
                        break;

                    case 7:
                        System.out.println(bank.toString());
                        break;

                    case 8:
                        System.out.println(client1.toString());
                        break;

                    case 9:
                        System.out.println("Exiting system.");
                        scanner.close();
                        return;

                    default:
                        System.out.println("Invalid option. Please select a valid number.");
                        break;
                }
            } catch (InputMismatchException e) {
                // Handle invalid input (like a string or character when expecting a number)
                System.out.println("Invalid Input Ignored. Please enter a valid number.");
                scanner.nextLine(); // Clear the buffer by consuming the invalid input
            }
        }
    }
}

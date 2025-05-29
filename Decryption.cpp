#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include<string>
#include <algorithm>  
#include <set>        // For tracking previously shown guesses
using namespace std;

// Updated fixed English letter frequency table 
const double fixedFreqTable[26] = {0.0817,0.0150,0.0278, 0.0425,0.1270,0.0223,0.0202,0.0609, 
 0.0697,0.0015,0.0077,0.0403,0.0241,0.0675,0.0751,0.0193,0.0010,0.0599,0.0633,0.0906,0.0276,0.0098,  
0.0236,0.0015,0.0197,0.0007   
};

// Function to decrypt the cipher text by shifting letters
string decrypt(const string& cipherText, int shift) 
{
    string decryptedText = "";
    for (char c : cipherText) 
	{
        if (isalpha(c)) 
		{
            char base = islower(c) ? 'a' : 'A';
            decryptedText += char((c - base - shift + 26) % 26 + base);
        } 
		else 
            decryptedText += c;  // Keep non-alphabetic characters unchanged
    }
    return decryptedText;
}

// Function to calculate frequency of letters in the decrypted text

vector<int> calculateLetterFrequency(const string& text) 
{
    vector<int> letterCount(26, 0);
    int totalLetters = 0;

    for (char c : text) 
	{
        if (isalpha(c)) 
		{
            c = toupper(c);          // Convert to uppercase for consistency
            letterCount[c - 'A']++;
            totalLetters++;
        }
    }

    return letterCount;
}

// Function to calculate how "close" a decrypted text is to standard English letter frequencies

double calculateScore(const vector<int>& letterCount)
{
    double score = 0.0;
    int totalLetters = 0;

    // Calculate the total number of letters in the decrypted text
    for (int count : letterCount) 
        totalLetters += count;
    

    // Calculate the frequency distribution of the text
    
    vector<double> textFreq(26, 0);
    for (int i = 0; i < 26; i++) 
        textFreq[i] = (double)letterCount[i] / totalLetters * 100.0;  
    

    // Compare the text's frequency distribution with English's distribution
    
    for (int i = 0; i < 26; i++) 
        score += pow(textFreq[i] - fixedFreqTable[i], 2);  // Euclidean distance (lower is better)
    

    return score;
}

// Function to get a guess based on fixed letter frequency distribution

string getFixedFrequencyGuess(const string& cipherText) 
{
    // Count the frequency of letters in the ciphertext
    
    vector<int> letterCount = calculateLetterFrequency(cipherText);

    // Create a vector of pairs (letter, frequency) and sort them by frequency in descending order
    
    vector<pair<char, int>> freqList;
    for (int i = 0; i < 26; i++) 
        if (letterCount[i] > 0) 
            freqList.push_back({char(i + 'A'), letterCount[i]});


    // Sort by frequency (most frequent letter comes first)
    
    sort(freqList.begin(), freqList.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second > b.second;
    });

    // Create a mapping from the most frequent letters in the ciphertext to the fixed frequency table
    
    vector<char> mappedLetters(26, '\0');
    for (int i = 0; i < min(26, (int)freqList.size()); i++) 
        mappedLetters[i] = freqList[i].first;

    // Create the decryption guess by replacing the mapped letters with the fixed frequency letters
    
    string decryptedText = cipherText;
    for (int i = 0; i < 26; i++)
	 {
        if (mappedLetters[i] != '\0') 
		{
            char cipherChar = mappedLetters[i];
            char plainChar = 'A' + i;
            // Replace cipherChar with the corresponding letter based on fixed frequency table
            for (char &c : decryptedText) 
                if (toupper(c) == cipherChar) 
                    c = plainChar;
        }
    }
    return decryptedText;
}
int main()
{
	string cipherText;

	cout << "Enter the encrypted text: ";
    getline(cin, cipherText);

    set<int> shownGuesses; // Track the guesses that have been shown
    int rounds = 0;
    bool satisfied = false;

    while (rounds < 6 && !satisfied) 
	{
        vector<pair<int, double>> shiftScores;

        // Try all 26 possible shifts and calculate the scores, skipping already shown shifts
        
        for (int i = 0; i < 26; i++) 
            if (shownGuesses.count(i) == 0) 
			{  
                int shiftKey = (i) % 26; 
                string decryptedText = decrypt(cipherText, shiftKey);  
                vector<int> letterCount = calculateLetterFrequency(decryptedText);
                double score = calculateScore(letterCount);
                shiftScores.push_back({i + 1, score}); 
            }

        // Sort shifts based on their score (lower score means better match)
        
        sort(shiftScores.begin(), shiftScores.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
            return a.second < b.second;  // Lower score means a better match
        });

        // Display the top 5 best guesses
        
        cout << "\nRound " << rounds + 1 << " - Top guesses:\n";
        int topN = min(5, (int)shiftScores.size());  // Show top 5 shifts
        for (int i = 0; i < topN; i++) 
		{
            int shift = shiftScores[i].first; 
            int shiftKey = (shift - 1) % 26; 
            string decryptedText = decrypt(cipherText, shiftKey);
            cout << "Shift " << shift-1<< ": " << decryptedText << " (Score: " << shiftScores[i].second << ")\n";
            shownGuesses.insert(shift - 1);  
        }

        // Get and display the fixed frequency table guess
        
        string fixedFreqGuess = getFixedFrequencyGuess(cipherText);
        cout << "\nFixed Frequency Table Guess: " << fixedFreqGuess << " (Strictly follows the frequency table)\n";

        // Ask the user to choose the best shift or type 0 for more guesses
        
        int choice;
        cout << "\nEnter the shift value you think is correct (1-25) or 0 for more guesses: ";
        cin >> choice;

        if (choice == 0) 
		{
            rounds++;  // Proceed to the next round
        } 
		else 
		{
            satisfied = true;  // User satisfied with the guess
            int finalShiftKey = choice % 26;  
            string finalDecryptedText = decrypt(cipherText, finalShiftKey); 
            cout << "Final Decrypted Text: " << finalDecryptedText << "\n";
        }
    }    
    if (!satisfied) 
        cout << "\nSorry we have already listed every possibility\n";
    }
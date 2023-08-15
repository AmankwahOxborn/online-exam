#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include <fstream>

using namespace std;

class Question {
public:
    string questionText;
    vector<string> choices;
    int correctChoice;

    Question(const string &text, const vector<string> &choices, int correct)
        : questionText(text), choices(choices), correctChoice(correct) {}

    Question(const string &text, const string &choice1, const string &choice2, const string &choice3, int correct)
        : questionText(text), correctChoice(correct) {
        choices.push_back(choice1);
        choices.push_back(choice2);
        choices.push_back(choice3);
    }
};

class Exam {
private:
    vector<Question> questions;
    int score;
    time_t startTime;
    time_t endTime;
    map<int, int> userAnswers; // Store the user's choice index

public:
    Exam() : score(0), startTime(0), endTime(0) {}

    void addQuestion(const Question &q) {
        questions.push_back(q);
    }

    void start() {
        startTime = time(NULL);
        cout << "Welcome to the Online Exam System!" << endl;
        for (size_t i = 0; i < questions.size(); ++i) {
            askQuestion(questions[i], i + 1);
        }
        endTime = time(NULL);
        cout << "Exam completed. Your score: " << score << "/" << questions.size() << endl;
        recordAnswers();
        printSummary();
    }

    void askQuestion(const Question &q, int questionNumber) {
        cout << "Question " << questionNumber << ": " << q.questionText << endl;
        for (size_t i = 0; i < q.choices.size(); ++i) {
            cout << i + 1 << ". " << q.choices[i] << endl;
        }

        int answer;
        cout << "Enter your choice (1-" << q.choices.size() << "): ";
        cin >> answer;
        userAnswers[questionNumber] = answer - 1; // Store user's choice index

        if (answer == q.correctChoice) {
            cout << "Correct!" << endl;
            ++score;
        } else {
            cout << "Incorrect." << endl;
        }
    }

    void recordAnswers() {
        // Record and store user answers for later analysis
    }

    void printSummary() {
        cout << endl << "Summary:" << endl;
        cout << "Total questions: " << questions.size() << endl;
        cout << "Correct answers: " << score << endl;
        cout << "Time taken: " << endTime - startTime << " seconds" << endl;
        
        cout << endl << "Review of Incorrect Answers:" << endl;
        for (map<int, int>::iterator it = userAnswers.begin(); it != userAnswers.end(); ++it) {
            int questionNumber = it->first;
            int userChoiceIndex = it->second;
            const Question &q = questions[questionNumber - 1];

            if (userChoiceIndex != q.correctChoice - 1) {
                cout << "Question " << questionNumber << ": " << q.questionText << endl;
                cout << "Your choice: " << q.choices[userChoiceIndex] << endl;
                cout << "Correct choice: " << q.choices[q.correctChoice - 1] << endl << endl;
            }
        }
    }
};

int main() {
    Exam exam;

    exam.addQuestion(Question("What is 2 + 25?", "23", "27", "35", 2));
    exam.addQuestion(Question("Which planet is closest to the sun?", "Venus", "Mercury", "Earth", 2));
    exam.addQuestion(Question("What gas do plants use for photosynthesis?", "Oxygen", "Carbon Dioxide", "Nitrogen", 2));
    exam.addQuestion(Question("What is the capital of France?", "London", "Paris", "Berlin", 2));
    exam.addQuestion(Question("Who wrote the play 'Romeo and Juliet'?", "William Shakespeare", "Jane Austen", "George Orwell", 1));
    exam.addQuestion(Question("What is the chemical symbol for gold?", "Au", "Ag", "Fe", 1));
    exam.addQuestion(Question("Which gas do plants release during photosynthesis?", "Oxygen", "Carbon Dioxide", "Nitrogen", 1));
    exam.addQuestion(Question("What is the largest mammal?", "Elephant", "Blue Whale", "Giraffe", 2));
    exam.addQuestion(Question("What is the chemical symbol for water?", "W", "H2O", "O2", 2));
    exam.addQuestion(Question("Who painted the Mona Lisa?", "Leonardo da Vinci", "Pablo Picasso", "Vincent van Gogh", 1));

    cout << "Initial questions added." << endl;

    exam.start();

    return 0;
}


# Quiz Management System Using C

## Mini Hackathon — C Programming Lab

- **Team number:** [TeamSeedhaHack]
- **Batch:** 58 
- **Team members:** [Aagam Jain], [Dhairya Chawala], [Garvit Nain]
- **Faculty-approved problem statement:** [Quiz management]

## Problem statement
Create a menu-driven C application that conducts multiple-choice quizzes, checks answers, calculates performance, saves attempt history, and shows a leaderboard.

## Objectives and features
- Three categories: C Programming, Computer Basics, General Knowledge.
- Five questions per attempt, randomly selected and ordered from eight per category.
- Four options per question; answer via 1=A, 2=B, 3=C, 4=D.
- Input validation, immediate feedback, percentage, and grade.
- Save scores to `scores.txt`; display history and top-ten attempts.
- Scores are stored locally. Each attempt is ranked separately, not aggregated by student.

## Concepts used
Variables, conditionals, loops, arrays, strings, structures, functions, pointers, `rand`, `qsort`, and file I/O (`fopen`, `fprintf`, `fgets`, `fclose`).

## Algorithm
1. Seed random number generator and display main menu.
2. Read and validate menu choice.
3. If Start Quiz, read name and category, shuffle question indices.
4. For five questions, display prompt/options, validate answer, update score.
5. Display score, percentage, and grade; append result to `scores.txt`.
6. If History, load valid saved results and display them.
7. If Leaderboard, sort loaded results by percentage (descending), then name; show top ten.
8. Repeat until Exit.

## Sample test cases (expected and actual)
See `test_cases.md` for a detailed manual test matrix. The question order changes between runs.

## Limitations
- No timer or GUI; terminal only.
- Up to 500 saved results loaded for history/leaderboard.
- Names must be non-empty and cannot contain `|`.
- `scores.txt` is plain text and not protected against manual editing.
- Pseudorandom shuffling is suitable for a classroom quiz, not secure exams.


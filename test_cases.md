# Quiz Management System — Test Cases

The randomized question order means the exact questions and final score depend on the answers entered. Use a fresh `scores.txt` when checking the empty-state cases.

| ID | Input / action | Expected output | Observed during automated test |
|---|---|---|---|
| T01 | Main menu `5` | Goodbye message; clean exit | PASS |
| T02 | Main menu `0`, then `5` | Invalid input warning; prompt again | PASS |
| T03 | Main menu `abc`, then `5` | Invalid input warning; prompt again | PASS |
| T04 | Main menu `2`, then `5` | Instructions displayed | PASS |
| T05 | Main menu `3` without score file | No saved results yet | PASS |
| T06 | Main menu `4` without score file | No saved results yet | PASS |
| T07 | Start quiz, blank name, then valid name | Reject blank name; continue | PASS |
| T08 | Start quiz, invalid category `4`, then `1` | Reject category 4 | PASS |
| T09 | Start quiz, answer `0`, then `1` | Reject answer 0; accept 1 | PASS |
| T10 | Finish 5 answers | Score between 0 and 5, saved file line | PASS |
| T11 | View history after quiz | Saved student and score shown | PASS |
| T12 | View leaderboard after quiz | Saved attempt shown | PASS |

## Manual demonstration script
1. Choose `2` to show instructions.
2. Choose `1`, enter a student name, select category `1`.
3. Enter `0` once to demonstrate validation; then answer each question with `1`-`4`.
4. Observe correctness feedback and final score.
5. Choose `3` to show saved attempt.
6. Choose `4` to show leaderboard.
7. Choose `5` to exit.

## Important
These observations cover the listed flows; classmates should also test each category and multiple saved attempts before the live demonstration.

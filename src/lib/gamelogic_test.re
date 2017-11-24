open Jest;

open Expect;

open GameLogic;

let board = [[0, 2], [4, 4]];

let empty = [[]];

describe(
  "transformBoard",
  () => {
    test("empty", () => expect(transformBoard(Up, [[]]) |> Array.of_list) |> toHaveLength(0));
    test("blanks", () => expect(transformBoard(Left, [[1, 0, 0, 1]])) |> toEqual([[2, 0, 0, 0]]));
    test("Up", () => expect(transformBoard(Up, board)) |> toEqual([[4, 2], [0, 4]]));
    test("Down", () => expect(transformBoard(Down, board)) |> toEqual(board));
    test("Left", () => expect(transformBoard(Left, board)) |> toEqual([[2, 0], [8, 0]]));
    test("Right", () => expect(transformBoard(Right, board)) |> toEqual([[0, 2], [0, 8]]))
  }
);

describe(
  "scoreBoard",
  () => {
    test("empty", () => expect(scoreBoard([[]])) |> toEqual(0));
    test("board", () => expect(scoreBoard(board)) |> toEqual(10))
  }
);

describe(
  "makeBoard",
  () => {
    test("x length", () => expect(makeBoard() |> Array.of_list) |> toHaveLength(4));
    test("y length", () => expect(makeBoard() |> List.hd |> Array.of_list) |> toHaveLength(4));
    test("score - min", () => expect(makeBoard() |> scoreBoard) |> toBeGreaterThanOrEqual(6));
    test("score - max", () => expect(scoreBoard(board)) |> toBeLessThanOrEqual(12))
  }
);

describe(
  "testGameover",
  () => {
    test("empty", () => expect(testGameover([[]])) |> toEqual(true));
    test("gameover", () => expect(testGameover([[2, 4], [4, 8]])) |> toEqual(true));
    test("up/down", () => expect(testGameover([[2, 4], [2, 8]])) |> toEqual(false));
    test("left/right", () => expect(testGameover([[2, 4], [8, 8]])) |> toEqual(false))
  }
);
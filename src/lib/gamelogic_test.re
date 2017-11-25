open Jest;

open Expect;

open GameLogic;

let board = [[0, 2], [4, 4]];

let empty = [[]];

describe(
  "transform",
  () => {
    test("empty", () => expect(transform(Up, [[]]) |> Array.of_list) |> toHaveLength(0));
    test("blanks", () => expect(transform(Left, [[1, 0, 0, 1]])) |> toEqual([[2, 0, 0, 0]]));
    test("Up", () => expect(transform(Up, board)) |> toEqual([[4, 2], [0, 4]]));
    test("Down", () => expect(transform(Down, board)) |> toEqual(board));
    test("Left", () => expect(transform(Left, board)) |> toEqual([[2, 0], [8, 0]]));
    test("Right", () => expect(transform(Right, board)) |> toEqual([[0, 2], [0, 8]]))
  }
);

describe(
  "score",
  () => {
    test("empty", () => expect(score([[]])) |> toEqual(0));
    test("board", () => expect(score(board)) |> toEqual(10))
  }
);

describe(
  "make",
  () => {
    test("x length", () => expect(make() |> Array.of_list) |> toHaveLength(4));
    test("y length", () => expect(make() |> List.hd |> Array.of_list) |> toHaveLength(4));
    test("score - min", () => expect(make() |> score) |> toBeGreaterThanOrEqual(6));
    test("score - max", () => expect(score(board)) |> toBeLessThanOrEqual(12))
  }
);

describe(
  "gameIsOver",
  () => {
    test("empty", () => expect(gameIsOver([[]])) |> toEqual(true));
    test("gameover", () => expect(gameIsOver([[2, 4], [4, 8]])) |> toEqual(true));
    test("up/down", () => expect(gameIsOver([[2, 4], [2, 8]])) |> toEqual(false));
    test("left/right", () => expect(gameIsOver([[2, 4], [8, 8]])) |> toEqual(false))
  }
);
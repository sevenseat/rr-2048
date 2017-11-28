open Jest;

open Expect;

open GameLogic;

let board = [[0, 2], [4, 4]];

let empty = [[]];

describe(
  "shift",
  () => {
    test("empty", () => expect(shift(Up, [[]]) |> Array.of_list) |> toHaveLength(0));
    test("blanks", () => expect(shift(Left, [[1, 0, 0, 1]])) |> toEqual([[2, 0, 0, 0]]));
    test("Up", () => expect(shift(Up, board)) |> toEqual([[4, 2], [0, 4]]));
    test("Down", () => expect(shift(Down, board)) |> toEqual(board));
    test("Left", () => expect(shift(Left, board)) |> toEqual([[2, 0], [8, 0]]));
    test("Right", () => expect(shift(Right, board)) |> toEqual([[0, 2], [0, 8]]))
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
  "addCell",
  () => {
    test("empty", () => [[]] |> addCell |> expect |> toEqual([[]]));
    test(
      "adds one cell",
      () =>
        [[0, 0], [0, 0]]
        |> addCell
        |> List.flatten
        |> List.filter((!==)(0))
        |> List.length
        |> expect
        |> toEqual(1)
    );
    test(">=2", () => [[0, 0], [0, 0]] |> addCell |> score |> expect |> toBeGreaterThanOrEqual(2));
    test("<=2", () => [[0, 0], [0, 0]] |> addCell |> score |> expect |> toBeLessThanOrEqual(4));
    test(
      "full",
      () =>
        [[8, 8], [8, 8]]
        |> addCell
        |> List.flatten
        |> Array.of_list
        |> expect
        |> toEqual([|8, 8, 8, 8|])
    )
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

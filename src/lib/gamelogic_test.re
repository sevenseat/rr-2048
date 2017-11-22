open Jest;

open Expect;

open GameLogic;

/* test("empty list", () => expect(transformHelper([])) |> toEqual([]));

   test("zero", () => expect(transformHelper([0])) |> toEqual([]));

   test("zero start", () => expect(transformHelper([0, 2])) |> toEqual([2]));

   test("zero list", () => expect(transformHelper([0, 0, 0, 0])) |> toEqual([]));

   test("consolidate 2", () => expect(transformHelper([2, 2, 3, 0])) |> toEqual([4, 3]));

   test("magic list", () => expect(transformHelper([2, 2, 2, 2])) |> toEqual([4, 4]));

   test("padright", () => expect(padRight(4, 0, [0, 2])) |> toEqual([0, 2, 0, 0]));

   test("padright2", () => expect(padRight(4, 0, [])) |> toEqual([0, 0, 0, 0]));

   test("padright3", () => expect(padRight(0, 0, [0, 2])) |> toEqual([0, 2])); */
test("transpose", () => expect(transpose([[1, 2], [3, 4]])) |> toEqual([[1, 3], [2, 4]]));

test(
  "orientBoard Left",
  () => expect(orientBoard(Left, PreTransform, [[1, 2], [3, 4]])) |> toEqual([[1, 2], [3, 4]])
);

test(
  "orientBoard Right",
  () => expect(orientBoard(Right, PreTransform, [[1, 2], [3, 4]])) |> toEqual([[2, 1], [4, 3]])
);

test(
  "orientBoard Up",
  () => expect(orientBoard(Up, PreTransform, [[1, 2], [3, 4]])) |> toEqual([[1, 3], [2, 4]])
);

test(
  "orientBoard Down",
  () => expect(orientBoard(Down, PreTransform, [[1, 2], [3, 4]])) |> toEqual([[3, 1], [4, 2]])
);

test("addcell", () => expect(addCell([[1, 0], [0, 2]])) |> toEqual([[1, 2], [0, 2]]));

test("scoreboard", () => expect(scoreBoard([[1, 0], [0, 2]])) |> toEqual(3));

type touchData = {
  x: float,
  y: float,
  time: float
};

type action =
  | TouchStart(touchData)
  | TouchEnd(touchData)
  | KeyDown(int);

type state = {touchStart: option(touchData)};

let component = ReasonReact.reducerComponent("EventLayer");

let getTouchData = (touchesType, event) => {
  let touch = touchesType(event)##item(0);
  {x: touch##screenX, y: touch##screenY, time: Js.Date.now()}
};

let getGesture = (start_, end_) => {
  let min = 4000.0;
  let speedDown = (end_.y -. start_.y) *. 10000.0 /. (end_.time -. start_.time);
  let speedRight = (end_.x -. start_.x) *. 10000.0 /. (end_.time -. start_.time);
  let isHoriz = abs_float(speedRight) > abs_float(speedDown);
  switch (
    isHoriz,
    (abs_float(speedRight) -. min > 0.0, speedRight > 0.0),
    (abs_float(speedDown) -. min > 0.0, speedDown > 0.0)
  ) {
  | (true, (true, true), _) => Some(GameLogic.Right)
  | (true, (true, false), _) => Some(GameLogic.Left)
  | (false, _, (true, true)) => Some(GameLogic.Down)
  | (false, _, (true, false)) => Some(GameLogic.Up)
  | _ => None
  }
};

let make = (~onAction, ~className=?, children) => {
  let keyReducer = (direction) =>
    ReasonReact.UpdateWithSideEffects({touchStart: None}, (_self) => onAction(direction));
  {
    ...component,
    initialState: () => {touchStart: None},
    reducer: (action, state) =>
      switch (action, state.touchStart) {
      | (KeyDown(37), _) => keyReducer(GameLogic.Left)
      | (KeyDown(38), _) => keyReducer(GameLogic.Up)
      | (KeyDown(39), _) => keyReducer(GameLogic.Right)
      | (KeyDown(40), _) => keyReducer(GameLogic.Down)
      | (KeyDown(_), _) => ReasonReact.NoUpdate
      | (TouchStart(td), _) => ReasonReact.Update({touchStart: Some(td)})
      | (TouchEnd(_td), None) => ReasonReact.NoUpdate
      | (TouchEnd(td), Some(start)) =>
        switch (getGesture(start, td)) {
        | Some(direction) =>
          ReasonReact.UpdateWithSideEffects({touchStart: None}, ((_self) => onAction(direction)))
        | None => ReasonReact.NoUpdate
        }
      },
    render: ({reduce}) =>
      <div
        onKeyDown=(reduce((e) => KeyDown(ReactEventRe.Keyboard.which(e))))
        onTouchStart=(reduce((e) => TouchStart(getTouchData(ReactEventRe.Touch.targetTouches, e))))
        onTouchEnd=(reduce((e) => TouchEnd(getTouchData(ReactEventRe.Touch.changedTouches, e))))
        onTouchMove=((e) => ReactEventRe.Touch.preventDefault(e))
        ?className
        tabIndex=0>
        (ReasonReact.arrayToElement(children))
      </div>
  }
};

This is another implementation of the Game [2048](http://2048game.com/) in
Reason React. It was my first Reason React project, and is basically a fork of
[LIU9293's implementation](https://github.com/LIU9293/reason-react-2048).

## Key Observations

* Reason React is really easy to pickup. I am not much more than a javascript
  tinkerer, yet I was able to develop this, starting from
  [Reason Scripts](https://github.com/reasonml-community/reason-scripts) within
  5-6 hours. The syntax proves very familiar for someone who knows javascript.
  It's readable and straightforward.
* It was jawdroppingly powerful
  * Pattern Matching is amazing! I was hooked from the first one I wrote. It
    allows the programmer to focus on the logic, as the implementation becomes
    very easy.
  * Encouraged by the toolset, I found myself quickly migrating to more
    functional-style programming. I avoided loops, and found myself writing
    **recursive code**!
  * Tuples are great too. I loved wrapping-together a few variables and treating
    them as a unit. Although I found the parentheses syntax kinda confusing.
    There were times when I had 3-4 open or closed parentheses side-by-side for
    a simple callback function.
  * I _loved_ the typechecking. I haven't programmed with types since the Java
    era. I can't believe that there was a bullet-proof typesystem that didn't
    require annotating everything. It just worked. I was floored when the
    typechecking found errors within my JSX. **Wowzers**.
* I did have a number of challenges that took a little while to work-through
  * I found the module system a bit confusing. I couldn't figure-out how to
    create private helper-functions without putting them within the definition
    of the public function. That ended-up working for this project, however it
    makes it impossible to share these helper functions wihtin the module, and
    it made unit testing harder.
  * Jest doesn't fully support Bucklescript, yet. I worked mostly with
    linked-lists, but those aren't well supported by Jest. I usually had to
    convert an list to an array for testing purposes.
  * ReasonML has limited documentation, but OCAML has a ton. For good or for
    bad, I found myself having to learn the OCAML syntax to get things done. The
    [playground](https://reasonml.github.io/try) proved invaluable, as I would
    paste-in OCAML and instantly get out Reason.
  * Similarly, I spent way too much time trying to figure out OCAML type
    definitions. I'm sure they will become second-nature, but they are not yet.
  - The native OCAML library is pretty limited. I found myself wishing for a
    number of javascript functions at times
  - Reason / Bucklescript / React is HEAVY. This very light applicaiton is 58kb
    gzipped.... My code is a few hundred lines... THat's a lot of library code.
    I was somewhat surprised to see how much of it was Bucklescript code to
    handle language features like Linked Lists and Currying.

All-in-all, it's been a very fun experience. And I'm amazed with the power. I'm
going to look for opportunities to use Reason, instead of javascript, going
forward.

## Todos

* [ ] Fix keyboard bindings.... Right now the user has to click first.
* [ ] Detect game-over
* [x] Gestures
* [ ] Delay adding new cells after transform for a fraction of a second
* [x] Retitle the page

# View example

An example of how to use a `sgl::Graphics::TileView`, to make "map transitions".

The *MyScene* implementation is implementing the transition itself, hardcoding values and stuff, the *Bis* implementation is using the `sgl::Scenes::Zone` to do the transition with a lot less code, and it's much more friendly to use.

## Building

```
cmake . -Bbuild
cmake --build build --config Debug
```
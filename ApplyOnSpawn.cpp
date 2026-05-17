void ApplyOnSpawn(Context& ctx, Object& obj) {
    if (obj.bullet.enabled) {
        Sound shotSound = LoadSound("Assets/Sounds/shot.mp3");
        PlaySound(shotSound);
    }
}
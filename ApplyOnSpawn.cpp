static SoundHandle cachedShotSound = nullptr;

void ApplyOnSpawn(Object obj) {  // Ошибка: пропущен &, объект копируется
    if (!obj.bullet.enabled) {
        return;
    }

    if (cachedShotSound == nullptr) {
        cachedShotSound = LoadSound("Assets/Sounds/shot.mp3");
    }

    if (cachedShotSound != nullptr) {
        PlaySound(cachedShotSound);
    }
}
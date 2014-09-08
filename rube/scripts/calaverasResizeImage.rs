/**
 * Resizes images according to pixels per unit.
 */
float pixelsPerUnit = 420;
    image[] imgs = getSelectedImages();
    for (uint i = 0; i < imgs.length; i++)
        imgs[i].setHeight( imgs[i].getPixelHeight() / pixelsPerUnit );

from PIL import Image

with open("/home/reclaire/Desktop/flower.png", "rb") as f:
    im = Image.open(f)
    im.load()
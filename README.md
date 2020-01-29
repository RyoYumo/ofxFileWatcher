# ofxFileWatcher
## Usage
```
using ofShaderWithFileWatcher = ofxFileWatcher<ofShader>;
using ofImageWithFileWatcher  = ofxFileWatcher<ofIamge>;

ofShaderWithFileWatcher shader;
ofImageWithFileWatcher  image;

void ofApp::loadShader(){
  shader.load("shader.vert", "shader.frag"); 
}
void ofApp::loadImage(){
  image.load("lenna.jpg");
}


loadShader();
loadImage();
ofAddListener(shader.getFileChangeEvent(), this, &ofApp::loadShader); // auto reload
ofAddListener(image.getFileChangeEvent(), this, &ofApp::loadImage); 

```

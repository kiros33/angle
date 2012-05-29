//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef COMPILER_CSSSHADERS_REWRITE_CSS_VERTEX_SHADER
#define COMPILER_CSSSHADERS_REWRITE_CSS_VERTEX_SHADER

#include "GLSLANG/ShaderLang.h"

#include "compiler/cssshaders/RewriteCSSShaderBase.h"

//
// Rewrites a CSS vertex shader's intermediate tree into a valid GLSL shader.
//

// Example original vertex shader:
/*

 void main() {
 }

 */

// Example rewritten vertex shader:
// "XXX" represents the hidden symbol suffix.
/*

 varying vec2 css_v_texCoordXXX;
 attribute vec2 css_a_texCoordXXX;
 void main(){
 (css_v_texCoordXXX = css_a_texCoordXXX);
 }

 */

class RewriteCSSVertexShader : public RewriteCSSShaderBase {
public:
    RewriteCSSVertexShader(TIntermNode* root, const TSymbolTable& symbolTable, const TString& hiddenSymbolSuffix)
        : RewriteCSSShaderBase(root, symbolTable, hiddenSymbolSuffix)
        , mHiddenTexCoordAttrName(kHiddenTexCoordAttrPrefix + hiddenSymbolSuffix) {}

    void rewrite();

private:
    static const char* const kUserTexCoordAttrName;
    static const char* const kHiddenTexCoordAttrPrefix;

    void insertTexCoordAttrDeclaration();
    void insertTexCoordVaryingDeclaration();
    void insertTexCoordVaryingAssignment(const TString& texCoordAttrName);
    
    TString mHiddenTexCoordAttrName;
};

#endif  // COMPILER_CSSSHADERS_REWRITE_CSS_VERTEX_SHADER
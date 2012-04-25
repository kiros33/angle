//
// Copyright (c) 2002-2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef COMPILER_REWRITE_CSS_SHADER_BASE
#define COMPILER_REWRITE_CSS_SHADER_BASE

#include "GLSLANG/ShaderLang.h"

#include "compiler/intermediate.h"
#include "compiler/InfoSink.h"

class TInfoSinkBase;

class RewriteCSSShaderBase {
public:
    RewriteCSSShaderBase(TIntermNode* treeRoot, const TString& hiddenSymbolSuffix, TInfoSinkBase& infoSink)
        : root(treeRoot)
        , texCoordVaryingName(kTexCoordVaryingPrefix + hiddenSymbolSuffix)
        , sink(infoSink)
        , numErrors(0) {}
    
    virtual void rewrite();
    TIntermNode* getNewTreeRoot() { return root; }
    
    // TODO: Remove.
    int getNumErrors() { return numErrors; }
    
    virtual ~RewriteCSSShaderBase() {}
    
protected:
    static const char* const kTexCoordVaryingPrefix;
    static const char* const kTexture2D;
    static const char* const kMain;
    
    TIntermConstantUnion* createVec4Constant(float x, float y, float z, float w);
    TIntermConstantUnion* createMat4IdentityConstant();
    TIntermSymbol* createGlobalVec4(const TString& name);
    TIntermSymbol* createGlobalMat4(const TString& name);
    TIntermSymbol* createUniformSampler2D(const TString& name);
    TIntermSymbol* createVaryingVec2(const TString& name);
    TIntermSymbol* createAttributeVec2(const TString& name);
    TIntermAggregate* createFunctionCall(const TString& name);
    void addArgument(TIntermNode* argument, TIntermAggregate* functionCall);
    TIntermBinary* createBinary(TOperator op, TIntermTyped* left, TIntermTyped* right);
    TIntermAggregate* createTexture2DCall(const TString& textureUniformName, const TString& texCoordVaryingName);
    TIntermAggregate* createDeclaration(TIntermNode* child);
    TIntermBinary* createGlobalVec4Initialization(const TString& symbolName, TIntermTyped* rhs);
    TIntermBinary* createGlobalMat4Initialization(const TString& symbolName, TIntermTyped* rhs);
    TIntermAggregate* createVoidFunction(const TString& name);
    
    void insertAtTopOfShader(TIntermNode* node);
    void insertAtEndOfShader(TIntermNode* node);
    void insertAtTopOfFunction(TIntermNode* node, TIntermAggregate* function);
    void insertAtEndOfFunction(TIntermNode* node, TIntermAggregate* function);
    void insertTexCoordVaryingDeclaration();
    
    TIntermAggregate* findFunction(const TString& name);
    void renameFunction(const TString& oldFunctionName, const TString& newFunctionName);
    bool isSymbolUsed(const TString& symbolName);
    
    TIntermNode* root;
    TString texCoordVaryingName;
    TInfoSinkBase& sink;
    int numErrors;
    
private:
    void createRootSequenceIfNeeded();
    TIntermAggregate* getOrCreateFunctionBody(TIntermAggregate* function);
};

#endif  // COMPILER_REWRITE_CSS_SHADER_BASE
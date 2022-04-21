#include "pch.h"
#include "Text.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Animator.h"

Text::Text(INT32 _maxlength) : Component(COMPONENT_TYPE::TEXT)
{
	mMaxLength = _maxlength;
}

Text::~Text()
{


}



void Text::InitFontData(shared_ptr<vector<FontType>> _fonttype)
{

	mFontType = _fonttype;
	CreateFontBuffer();
	
}

void Text::SetSentence(const char* _sentnece)
{
	 mSentence = _sentnece; 
	 mLength = strlen(mSentence);
	 if (mLength > mMaxLength)
		 mLength = mMaxLength;
	 UpdateSentence();


}

void Text::CreateFontBuffer()
{
	Vertex* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	int vertexcount = 6 * mMaxLength;
	int indexcount = 6 * mMaxLength;
	int length = mMaxLength;

	shared_ptr<Mesh> _mesh = mGameObject.lock()->GetAnimator()->GetMesh();


	vertices = new Vertex[vertexcount];

	indices = new unsigned long[indexcount];

	memset(vertices, 0, (sizeof(Vertex) * vertexcount));


	for (i = 0; i < indexcount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexcount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	ID3D11Buffer* meshVertexBuffer;

	// Create the vertex buffer.
	result = GEngine->GetGraphicsProcessor()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &meshVertexBuffer);

	_mesh->SetVertexBuffer(meshVertexBuffer, vertexcount);

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexcount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	ID3D11Buffer* meshIndexBuffer = _mesh->GetIndexBuffer();

	// Create the index buffer.
	result = GEngine->GetGraphicsProcessor()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &meshIndexBuffer);
	_mesh->SetInexBuffer(meshIndexBuffer, indexcount);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete[] indices;
	indices = 0;



}

bool Text::UpdateSentence()
{
	
	Vertex* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Vertex* verticesPtr;

	shared_ptr<Mesh> _mesh = mGameObject.lock()->GetAnimator()->GetMesh();

	// Check for possible buffer overflow.
	if (mLength > mMaxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new Vertex[6 * mLength];
	if (!vertices)
	{
		return false;
	}
	memset(vertices, 0, (sizeof(Vertex) * 6 * mLength));


	drawX = 0.f; //(float)(((WINFO.ClientWidth / 2) * -1) + positionX);
	drawY = 0.f;// (float)((WINFO.ClientHeight / 2) - positionY);



	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	BuildVertexArray((void*)vertices, mSentence, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	auto k = _mesh->GetVertexBuffer();
	if (k == nullptr)
		int a = 5;

	auto context = GEngine->GetGraphicsProcessor()->GetDeviceContext();


	result = context->Map(_mesh->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}



	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (Vertex*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(Vertex) * 6 * mLength));

	// Unlock the vertex buffer.
	context->Unmap(_mesh->GetVertexBuffer(), 0);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;


	_mesh->SetVertexCount(6 * mLength);
	_mesh->SetIndexCount(6 * mLength);
	return true;
}

void Text::BuildVertexArray(void* vertices, const char* sentence, float drawX, float drawY)
{
	Vertex* vertexPtr;
	int numLetters, index, i, letter;

	FontType* data = mFontType->data();
	


	// Coerce the input vertices into a VertexType structure.
	vertexPtr = (Vertex*)vertices;
	
	// Get the number of letters in the sentence.
	numLetters = mLength;

	// Initialize the index to the vertex array.
	index = 0;

	// Draw each letter onto a quad.
	for (i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;
		
		// If the letter is a space then just move over three pixels.
		if (letter == 0)
		{
			drawX = drawX + 3.0f;
		}
		else
		{
			
			// First triangle in quad.
			vertexPtr[index].Pos = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].Tex = XMFLOAT2(data[letter].left, 0.0f);
			
			index++;

			vertexPtr[index].Pos = XMFLOAT3((drawX + data[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].Tex = XMFLOAT2(data[letter].right, 1.0f);
			index++;

			vertexPtr[index].Pos = XMFLOAT3(drawX, (drawY - 16), 0.0f);  // Bottom left.
			vertexPtr[index].Tex = XMFLOAT2(data[letter].left, 1.0f);
			index++;

			// Second triangle in quad.
			vertexPtr[index].Pos = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].Tex = XMFLOAT2(data[letter].left, 0.0f);
			index++;

			vertexPtr[index].Pos = XMFLOAT3(drawX + data[letter].size, drawY, 0.0f);  // Top right.
			vertexPtr[index].Tex = XMFLOAT2(data[letter].right, 0.0f);
			index++;

			vertexPtr[index].Pos = XMFLOAT3((drawX + data[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].Tex = XMFLOAT2(data[letter].right, 1.0f);
			index++;

			// Update the x location for drawing by the size of the letter and one pixel.
			drawX = drawX + data[letter].size + 1.0f;

		}
	}





}

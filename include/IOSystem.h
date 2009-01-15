/*
---------------------------------------------------------------------------
Open Asset Import Library (ASSIMP)
---------------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team

All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file IOSystem.h
 *  @brief File system wrapper for C++. Inherit this class to supply
 *  custom file handling logic to the Import library.
*/

#ifndef AI_IOSYSTEM_H_INC
#define AI_IOSYSTEM_H_INC

#ifndef __cplusplus
#	error This header requires C++ to be used. aiFileIO.h is the \
	corresponding C interface.
#endif


#include "aiTypes.h"
namespace Assimp	{

class IOStream;

// ---------------------------------------------------------------------------
/** @class IOSystem
*   @brief Interface to the file system.
*
* Derive an own implementation from this interface to supply custom file handling
* to the importer library. If you implement this interface, you also want to
* supply a custom implementation for IOStream.
*/
class ASSIMP_API IOSystem
{
public:
	/** @brief Constructor. Create an instance of your derived class and
	 * assign it to an #Assimp::Importer instance by calling Importer::SetIOHandler().
	 */
	IOSystem();

	/** Destructor. */
	virtual ~IOSystem();

	// -------------------------------------------------------------------
	/** @brief Tests for the existence of a file at the given path. 
	*
	* @param pFile Path to the file
	* @return true if there is a file with this path, else false.
	*/
	virtual bool Exists( const std::string& pFile) const = 0;

	// -------------------------------------------------------------------
	/**	@brief Returns the system specific directory separator
	*	@return	System specific directory separator
	*/
	virtual std::string getOsSeparator() const = 0;

	// -------------------------------------------------------------------
	/** @brief Open a new file with a given path.
	*
	*  When the access to the file is finished, call Close() to release
	*  all associated resources.
	*
	* @param pFile Path to the file
	* @param pMode Desired file I/O mode. Required are: "wb", "w", "wt",
	*        "rb", "r", "rt".
	*
	* @return New IOStream interface allowing the lib to access
	*         the underlying file. 
	* @note When implementing this class to provide custom IO handling, 
	* you probably have to supply an own implementation of IOStream as well. 
	*/
	virtual IOStream* Open(
		const std::string& pFile,
		const std::string& pMode = std::string("rb")) = 0;

	// -------------------------------------------------------------------
	/** @brief Closes the given file and releases all resources associated with it.
	 *  @param pFile The file instance previously created by Open().
	 */
	virtual void Close( IOStream* pFile) = 0;


	// -------------------------------------------------------------------
	/** @brief Compares two paths and check whether the point to
	 *         identical files.
	 *  
	 * The dummy implementation of this virtual performs a 
	 * case-insensitive comparison of the given strings. The default IO
	 * system implementation uses OS mechanisms to convert relative into
	 * absolute paths, so the result can be trusted.
	 * @param one First file
	 * @param second Second file
	 * @return true if the paths point to the same file. The file needn't
	 *   be existing, however.
	 */
	virtual bool ComparePaths (const std::string& one, 
		const std::string& second);
};

// ----------------------------------------------------------------------------
inline IOSystem::IOSystem() 
{
	// empty
}

// ----------------------------------------------------------------------------
inline IOSystem::~IOSystem() 
{
	// empty
}
// ----------------------------------------------------------------------------


} //!ns Assimp

#endif //AI_IOSYSTEM_H_INC

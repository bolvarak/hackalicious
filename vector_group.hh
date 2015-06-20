<?hh

/**
 * Needed Libraries
 */
require_once('array_to_collection.hh');

/**
 * This function groups a vector into a Map of vectors
 * @name vector_group()
 * @param  Vector<mixed> $vecSource
 * @param  string        $strKey
 * @return Map<string, Vector<Map<string, mixed>>>
 */
function vector_group(Vector<mixed> $vecSource, string $strKey) : Map<mixed, Vector<Map<string, mixed>>>
{
	// Create a response map
	$mapReturn = Map {};
	// Iterate over the vector
	foreach ($vecSource->getIterator() as $intIndex => $mixValue) {
		// Check for an array
		if (is_array($mixValue)) {
			// Convert it
			$mixValue = array_to_collection($mixValue);
		}
		// Check for a key in the map
		if ($mapReturn->contains($mixValue->get($strKey)) === false) {
			// Create the key
			$mapReturn->set($mixValue->get($strKey), Vector {});
		}
		// Set the value
		$mapReturn->get($mixValue->get($strKey))->add($mixValue);
	}
	// Return the map
	return $mapReturn;
}

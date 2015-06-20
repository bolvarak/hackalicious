<?hh

/**
 * Needed Libraries
 */
require_once('array_is_associative.hh');
require_once('array_to_map.hh');
require_once('array_to_vector.hh');

/**
 * This method converts an array to a collection type of either a Vector or a Map
 * @name array_to_collection()
 * @param array<mixed, mixed> $arrSource
 * @return Map<string, mixed>|Vector<mixed>
 */
function array_to_collection(array $arrSource) : mixed
{
	// Check for an associative array
	if (array_is_associative($arrSource) === true) {
		// Return the data
		return array_to_map($arrSource);
	} else {
		// Return the data
		return array_to_vector($arrSource);
	}
}

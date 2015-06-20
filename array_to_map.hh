<?hh

/**
 * Needed Libraries
 */
require_once('array_is_associative.hh');
require_once('array_to_map.hh');
require_once('array_to_vector.hh');

/**
 * This method recursively converts an associative array for a Map
 * @name array_to_map()
 * @param array<string, mixed> $arrData
 * @return Map<string, mixed>
 */
function array_to_map(array $arrData) : Map<string, mixed>
{
	// Set the return variable
	$mapReturn = Map {};
	// Iterate over the array
	foreach ($arrData as $strKey => $mixValue) {
		// Check the value
		if (is_array($mixValue) && array_is_associative($mixValue)) {
			// Set the value
			$mapReturn->set($strKey, array_to_map($mixValue));
		} elseif (is_array($mixValue)) {
			// Set the value
			$mapReturn->set($strKey, array_to_vector($mixValue));
		} else {
			// Set the value
			$mapReturn->set($strKey, $mixValue);
		}
	}
	// Return the map
	return $mapReturn;
}

<?hh

/**
 * This function implodes a vector of maps based on the map key $strNeedle
 * @name vectormap_implode()
 * @param  Vector<Map<string, mixed>> $vecHaystack
 * @param  string                     $strNeedle
 * @param  string                     $strDelimiter [','']
 * @return string
 */
function vectormap_implode(Vector<Map<string, mixed>> $vecHaystack, string $strNeedle, string $strDelimiter = ',') : string
{
	// Create the values vector
	$vecNeedles = new Vector();
	// Iterate over the vector
	foreach ($vecHaystack->getIterator() as $intIndex => $mapValue) {
		// Check for the needle
		if ($mapValue->contains($strNeedle)) {
			// Append the needle
			$vecNeedles->add($mapValue->get($strNeedle));
		}
	}
	// Return the string
	return implode($strDelimiter, $vecNeedles->toArray());
}

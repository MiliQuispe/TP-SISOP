#!/usr/bin/awk -f
BEGIN {
    FS = ","
    total_ids = 0
    max_id = 0
}

NR == 1 { next }  # Saltar encabezado

{
    id = $1 + 0
    ids_seen[id]++
    if (id > max_id) max_id = id
    total_ids++
}

END {
    # Verificar duplicados
    duplicates = 0
    for (id in ids_seen) {
        if (ids_seen[id] > 1) {
            print "❌ ID duplicado:", id
            duplicates++
        }
    }
    
    # Verificar que todos los IDs del 1 al max_id existen
    missing = 0
    for (i = 1; i <= max_id; i++) {
        if (!ids_seen[i]) {
            print "❌ ID faltante:", i
            missing++
        }
    }
    
    print "=== RESUMEN ==="
    print "Total registros:", total_ids
    print "ID máximo:", max_id
    print "IDs duplicados:", duplicates
    print "IDs faltantes:", missing
    
    if (duplicates == 0 && missing == 0) {
        print "✅ ÉXITO: IDs correlativos y únicos (aunque posiblemente desordenados)"
    } else {
        print "❌ FALLÓ: Problemas con los IDs"
    }
}
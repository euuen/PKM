# 例子

```vue
<script setup lang="ts">
import { ref, onMounted } from 'vue'

const container = ref(null)

onMounted(()=> {
	container.value.innerHTML = 'hello world!'
})
</script>


<template>
	<div ref="container"></div>
</template>
```
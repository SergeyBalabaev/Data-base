# Foxgres-UI

Для ускорения разработки предалагается использовать готовые компоненты из **material-ui**

Описывать стили без использования CSS
Предпочтительней использовать `styled` из MUI

```tsx
import { styled } from '@mui/material';

const StyledDiv = styled('div')`
   width: 200px;
   height: 200px;
`;

<StyledDiv />
```

TBC
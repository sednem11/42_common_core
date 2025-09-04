import '@fastify/jwt';

declare module '@fastify/jwt' {
  interface FastifyJWT {
    payload: {
      id: number;
      username: string;
      requires2FA: boolean;
    }
    user: {
      id: number;
      username: string;
      requires2FA: boolean;
    }
  }
}